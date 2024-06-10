#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

int connectedClients;
struct clientInfo
{
    int socket;
    char name[16];
};
struct clientInfo players[8];
int loadPlayers(int *sock);
int openServer(int *sock, struct sockaddr_in *sin, int *bs);
void sendMessageToPlayer(int player, const char *message);
int main(void)
{
    int s_socket, bind_socket;
    struct sockaddr_in server_adress;
    openServer(&s_socket, &server_adress, &bind_socket);
    loadPlayers(&s_socket);
    char himsg[] = "hello there player 1";
    sendMessageToPlayer(0, himsg);
}

int openServer(int *sock, struct sockaddr_in *sin, int *bs)
{
    *sock = socket(AF_INET, SOCK_STREAM, 0);
    if (*sock < 0)
    {
        printf("failed to create socket\n");
        return -1;
    }

    memset(sin, 0, sizeof(*sin));
    sin->sin_family = AF_INET;
    sin->sin_port = htons(9000);
    sin->sin_addr.s_addr = inet_addr("127.0.0.1");

    *bs = bind(*sock, (struct sockaddr *)sin, sizeof(*sin));
    if (*bs < 0)
    {
        printf("failed to bind to server\n");
        close(*sock);
        return -1;
    }
    if (listen(*sock, 8) < 0)
    {
        printf("Listen failed\n");
        close(*sock);
        return -1;
    }

    return 0;
}
int loadPlayers(int *sock)
{
    int connectedClient = 0;
    while (connectedClient < 8)
    {
        int temp_socket = accept(*sock, NULL, NULL);
        players[connectedClient].socket = temp_socket;

        int bytes;

        bytes = recv(temp_socket, players[connectedClient].name, sizeof(players[connectedClient].name), 0);
        players[connectedClient].name[bytes] = '\0';
        printf(players[connectedClient].name);
        printf("\nclient :%d connected\n", connectedClient + 1);
        connectedClient++;
    }
    printf("all players sucessfully loaded in");
}
void sendMessageToPlayer(int playerIndex, char *msg)
{
    int player_socket = players[playerIndex].socket;
    int bytes = send(player_socket, msg, sizeof(msg), 0);
    if (bytes < 0)
    {
        printf("Failed to send message to  %d\n", playerIndex);
    }
}
void receiveMessageFromPlayer(int playerIndex, char *msg)
{

    int bytes;
    bytes = recv(players[playerIndex].socket, msg, sizeof(msg) - 1, 0);
    if (bytes < 0)
    {
        printf("receive failed");
        return;
    }
    msg[bytes] = '\0';
}