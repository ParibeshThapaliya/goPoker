#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <WINDOWS.H>

#include "client.h"

void example();

int main(int argc, char *argv[]) {
    struct hostent *server;
    struct sockaddr_in server_addr;

    if (argc < 3) {
        fprintf(stderr, "Error command line, please run like this: %s ip port\n", argv[0]);
        return 1;
    }

    WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
    if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);;

    g_socket = socket(AF_INET, SOCK_STREAM, 0);
 
    if (connect(g_socket, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)) < 0) {
        fprintf(stderr, "connecting to server failed");
        return 1;
    }

    printf("connect %d\n", g_socket);

    /*
     * Has connected to server successfully, add other code here
     */

    example();

    return 0;
}

void example() {
    char buffer[MESSAGE_SIZE];
    strcpy(buffer, "ENTER Jane SEAT 1 PAASWORD secret");
    int n = send_to_server(buffer, strlen(buffer));
    n = receive_from_server(buffer, MESSAGE_SIZE);
    printf("Get response %s\n", buffer);
}

int send_to_server(const void *buffer, int count) {
    return send(g_socket, buffer, count, 0);
}

int receive_from_server(void *buffer, int count) {
    memset(buffer, 0, count);
    return recv(g_socket, buffer, count, 0);
}

int communicate_with_server(const void *send_buffer, int send_count, void *receive_buffer, int receive_count) {
    int res;

    res = send_to_server(send_buffer, send_count);

    if (res < 0) {
        fprintf(stderr, "send to  server failed\n");
        return -1;
    }

    res = receive_from_server(receive_buffer, receive_count);
    if (res < 0) {   
        fprintf(stderr, "receive from server failed\n");
    }

    return res;
}

