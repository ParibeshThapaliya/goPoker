#ifndef CLIENT_H__
#define CLIENT_H__

#define MESSAGE_SIZE 4096

int g_socket; // Use this socket to communicate with server

/**
 * Send message to server, if success, return the bytes count has been send to server,
 * otherwise, return -1
 */
int send_to_server(const void *buffer, int count);

/**
 * Receive message from server, if success, return the bytes count has been read from server,
 * otherwise, return -1 if error, return 0 if connection has been closed.
 */
int receive_from_server(void *buffer, int count);

/**
 * Send message to server, and receive response from server, 
 * if success, return the bytes count has been read from server,
 * otherwise, return -1 if error, return 0 if connection has been closed.
 */
int communicate_with_server(const void *send_buffer, int send_count, void *receive_buffer, int receive_count);

#endif