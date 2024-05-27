#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#define closesocket close
typedef int SOCKET;
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR   (-1)
#endif

#include "client.h"
#include "../GUI/GUI.h"

void example();
SOCKET g_socket;

int main(int argc, char *argv[]) {
    struct hostent *server;
    struct sockaddr_in server_addr;

    if (argc < 3) {
        fprintf(stderr, "Error command line, please run like this: %s ip port\n", argv[0]);
        return 1;
    }

#ifdef _WIN32
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(sockVersion, &wsaData) != 0) {
        return 0;
    }
#endif

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    g_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (g_socket == INVALID_SOCKET) {
        fprintf(stderr, "Socket creation failed\n");
        return 1;
    }

    if (connect(g_socket, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)) < 0) {
        fprintf(stderr, "Connecting to server failed\n");
        closesocket(g_socket);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    printf("Connected %d\n", g_socket);

    example();

    // Initialize the GUI
    init_gui(&argc, &argv);

    // Create the main window
    GtkWidget *main_window = create_main_window();

    // Show the main window
    gtk_widget_show_all(main_window);

    // Start the GTK main loop
    gtk_main();

    // Cleanup
    closesocket(g_socket);
#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}

void example() {
    char buffer[MESSAGE_SIZE];
    strcpy(buffer, "ENTER Jane SEAT 1 PASSWORD secret");
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
        fprintf(stderr, "Send to server failed\n");
        return -1;
    }

    res = receive_from_server(receive_buffer, receive_count);
    if (res < 0) {   
        fprintf(stderr, "Receive from server failed\n");
    }

    return res;
}
