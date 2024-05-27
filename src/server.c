#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <ctype.h>

#include "server.h"

struct Client *g_clients = NULL;

void process_requests_with_loop(int socket);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error command line, please run like this: %s port\n", argv[0]);
        return 1;
    }

    int socket = create_server(atoi(argv[1]));

    process_requests_with_loop(socket);

    return 0;
}

int create_server(unsigned short port) {
    int server_socket, res;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    res = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (res == -1) {
      fprintf(stderr, "Socket can't be bind\n");
      return -1;
    }

    res = listen(server_socket, 5);
    if (res == -1) {
      fprintf(stderr, "Socket can't be listened on\n");
      return -1;
    }

    return server_socket;
}

/**
 * Split one string by empty character, remember to free (*table) later.
 * 
 * For example:
 *      char **args;
 *      int argc;
 *      char str[256] = "ENTER Jane SEAT 1 PAASWORD secret";
 *      split_str(str, &args, &argc); 
 *      // argc is 6, args[0] is "ENTER", args[1] is "Jane", args[2] is "SEAT"
 *      // ..., args[5] is "secret"
 *      ...
 *      free(args);      
 */
void split_str(char *str, char ***table, int *length) {
    int count = 1;
    int strLen = strlen(str);

    if (strLen == 0) {
        *table = NULL;
        *length = 0;
        return;
    }

    // Compute how many substring will be splited
    for (int i = 0; i < strLen; i++) {
        if (isspace(str[i])) {
            str[i] = '\0';
        }
        if ((i == 0 || str[i-1] == '\0') && str[i] != '\0') {
            count++;
        }
    }

    // Set all substring entry in table
    *table = (char**)malloc(sizeof(char*) * count);
    count = 0;
    for (int i = 0; i < strLen; i++) {
        if ((i == 0 || str[i-1] == '\0') && str[i] != '\0') {
            (*table)[count++] = str + i;
        }
    }
    *length = count;
}

int process_request(int client_socket) {
    int n, count;
    char buffer_bk[MESSAGE_SIZE];
    char buffer[MESSAGE_SIZE];
    char name[MAX_NAME_LEN];
    char **args;
    int argc;

    memset(buffer, 0, MESSAGE_SIZE);

    // Read request message frome client
    n = recv(client_socket, buffer, MESSAGE_SIZE, 0);
    if (n <= 0) { // Read failed or connection closed
        get_name_by_socket(client_socket, name);
        printf("%s exit\n", name);
        remove_client_by_socket(client_socket);
        return n;
    } else {
        strcpy(buffer_bk, buffer);
        split_str(buffer, &args, &argc);
        /* 
         * to do
         */
        if (argc == 6 && strcmp(args[0], "ENTER") == 0) {
            strcpy(name, args[1]);
            add_client(client_socket, name);
            sprintf(buffer, "OK SEAT=%s NAME=%s POINTS=0\n", args[3], name);
        } else {
            get_name_by_socket(client_socket, name);
            sprintf(buffer, "ERROR invalid message \"%s\"\n", buffer_bk);
        }
        return send_to_client(name, buffer, strlen(buffer));
    }
}

void process_requests_with_loop(int socket) {
    struct sockaddr_in client_addr;
    socklen_t slen = sizeof(client_addr);
    fd_set rfds, rfds_bk;
    int nfd = socket+1;
    int res;
    int client_socket;
    struct timeval t;

    // Set time to 1 second
    t.tv_sec = 1;
    t.tv_usec = 0;

    FD_ZERO(&rfds_bk);
    FD_SET(socket, &rfds_bk);

    printf("Start loop %d\n", socket);

    while (1) {
        rfds = rfds_bk;
        res = select(nfd, &rfds, NULL, NULL, NULL/*&t*/);
        if (res < 0) {
            if (errno == EINTR)
            {
                continue;
            }
            fprintf(stderr, "select failed\n");
            return;
        } else if (res == 0) {
            // Timeout, continue to select
            continue;
        }
        for (int i = 0; i < nfd; i++) {
            if (FD_ISSET(i, &rfds)) {
                if (i == socket) {
                    client_socket = accept(
                        socket, (struct sockaddr *)&client_addr, &slen);
                    // printf("A new connection has been accepted %d\n", client_socket);
                    if (client_socket >= nfd) {
                        nfd = client_socket+1;
                    }
                    FD_SET(client_socket, &rfds_bk);
                } else {
                    // printf("read event %d\n", i);
                    res = process_request(i);
                    if (res <= 0) {
                        FD_CLR(i, &rfds_bk);
                    }
                }
            }
        }
    }
}

struct Client* find_client_by_name(const char *name) {
    struct Client* p = g_clients;
    while (p != NULL) {
        if (strcmp(p->name, name) == 0) {
            return p;
        } 
        p = p->next;
    }
    return NULL;
}

struct Client* find_client_by_socket(int socket) {
    struct Client* p = g_clients;
    while (p != NULL) {
        if (p->socket == socket) {
            return p;
        } 
        p = p->next;
    }
    return NULL;
}

void add_client(int socket, const char *name) {
    struct Client* p = (struct Client*)malloc(sizeof(struct Client));
    p->socket = socket;
    strcpy(p->name, name);
    p->next = g_clients;
    g_clients = p;
}

void remove_client_by_name(const char *name) {
    struct Client* p = g_clients, *prev = NULL;
    while (p != NULL) {
        if (strcmp(p->name, name) == 0) {
            break;
        } 
        prev= p;
        p = p->next;
    }
    if (p != NULL) {
        if (prev == NULL) {
            g_clients = p->next;
            free(p);
        } else {
            prev->next = p->next;
            free(p);
        }
    }
}

void remove_client_by_socket(int socket) {
    struct Client* p = g_clients, *prev = NULL;
    while (p != NULL) {
        if (p->socket == socket) {
            break;
        } 
        prev= p;
        p = p->next;
    }
    if (p != NULL) {
        if (prev == NULL) {
            g_clients = p->next;
            free(p);
        } else {
            prev->next = p->next;
            free(p);
        }
    }
}

void print_all_clients() {
    struct Client* p = g_clients;
    printf("Clients: ");
    while (p != NULL) {
        printf("%s %d\t", p->name, p->socket);
        p = p->next;
    }
    printf("\n");
}

int send_to_client(const char *name, const void *buffer, int count) {
    struct Client* p = find_client_by_name(name);
    if (p == NULL) {
        return -1;
    }
    return send(p->socket, buffer, count, 0);
}

int get_name_by_socket(int socket, char *name) {
    struct Client* p = find_client_by_socket(socket);
    if (p == NULL) {
        return 0;
    }
    strcpy(name, p->name);
    return 1;
 
}