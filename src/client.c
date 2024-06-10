#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <poll.h>
char name[16];

int openConnection(int *sock, struct sockaddr_in *sin, int *cs);
int receiveServerMsg(int *sock, char *serverResponse, size_t responseSize);
int sendServerMsg(int *sock, char *clientResponse, size_t responseSize);
int main(int argc, char *argv[])
{
    int connectStatus;
    int g_socket, connet_status;
    struct sockaddr_in server_adress;
    char message[4096];
    struct pollfd fds[2];

    if ((connectStatus = openConnection(&g_socket, &server_adress, &connet_status)) != 0)
    {
        printf("failed to initialize connection to the server ");
        return -1;
    }
    fds[0].fd = g_socket;
    fds[0].events = POLLIN; // Check for incoming data

    while (1)
    {
        int poll_count = poll(fds, 1, 1000); // Poll with a timeout of 1000ms

        if (poll_count == -1)
        {
            printf("Poll error.\n");
            close(g_socket);
            return -1;
        }

        if (poll_count == 0)
        {
            printf("Poll timed out, no data received.\n");
            continue;
        }

        if (fds[0].revents & POLLIN)
        {
            if (receiveServerMsg(&g_socket, message, sizeof(message)) == 0)
            {
                printf("Received from server: %s\n", message);
            }
            else
            {
                printf("Failed to receive message.\n");
            }
        }
    }
    close(g_socket);
}

int openConnection(int *sock, struct sockaddr_in *sin, int *cs)
{
    *sock = socket(AF_INET, SOCK_STREAM, 0);
    if (*sock < 0)
    {
        printf("cannt create socket");
        return -1;
    }

    sin->sin_family = AF_INET;
    sin->sin_port = htons(9000);
    sin->sin_addr.s_addr = inet_addr("127.0.0.1");
    if (inet_pton(AF_INET, "127.0.0.1", &(sin->sin_addr)) <= 0)
    {
        printf("wrong adress");
        close(*sock);
        return -1;
    }

    *cs = connect(*sock, (struct sockaddr *)sin, sizeof(*sin));
    if (*cs < 0)
    {
        printf("failed to connect to server, pls try again and make sure server is setup");
        close(*sock);
        return -1;
    }
    return 0;
}
int receiveServerMsg(int *sock, char *serverResponse, size_t responsesize)
{
    int bytes;

    bytes = recv(sock, serverResponse, responsesize - 1, 0);
    if (bytes < 0)
    {
        printf("receive failed");
        return -1;
    }
    serverResponse[bytes] = '\0';
    return 0;
}

int sendServerMsg(int *sock, char *clientResponse, size_t responsesize)
{
    size_t sendSize;
    sendSize = send(sock, clientResponse, responsesize, 0);
    if (sendSize < 0)
    {
        printf("failed to send");
        return -1;
    }
    return sendSize;
}