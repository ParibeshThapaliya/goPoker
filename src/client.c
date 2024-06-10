#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <poll.h>
#include <string.h>

#include "Structures.h"
#include "GameHandling.h"
#include "CheckWin.h"
#include "GUI.h"
char name[16];
static void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}
int openConnection(int *sock, struct sockaddr_in *sin, int *cs);
int receiveServerMsg(int *sock, char *serverResponse);
int sendServerMsg(int *sock, char *clientResponse);
int main(int argc, char *argv[])
{
    strcpy(name, argv[1]);
    int connectStatus;
    int g_socket, connet_status;
    struct sockaddr_in server_adress;
    char message[4096];

    GtkWidget *window;
    GtkWidget *button;

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(window), 500);

    button = gtk_button_new_with_label("Click Me!");
    gtk_container_add(GTK_CONTAINER(window), button);
    gtk_widget_show_all(window);
    gtk_main();

    if ((connectStatus = openConnection(&g_socket, &server_adress, &connet_status)) != 0)
    {
        printf("failed to initialize connection to the server ");
        return -1;
    }
    receiveServerMsg(&g_socket, message);
    printf("Received from server: %s\n", message);
    close(g_socket);
    return 0;
}
int intializeMenu()
{
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
    else
    {
        // char name[] = "name1";
        sendServerMsg(sock, name);
    }
    return 0;
}
int receiveServerMsg(int *sock, char *serverResponse)
{
    int bytes;

    bytes = recv(*sock, serverResponse, sizeof(serverResponse) - 1, 0);
    if (bytes < 0)
    {
        printf("receive failed");
        return -1;
    }
    serverResponse[bytes] = '\0';
    return 0;
}

int sendServerMsg(int *sock, char *clientResponse)
{
    size_t sendSize;
    sendSize = send(*sock, clientResponse, sizeof(clientResponse), 0);
    if (sendSize == -1)
    {
        printf("failed to send");
        return -1;
    }
    return sendSize;
}