#include "client.h"
#include "server.h"
#include "GUI.h"
#include <pthread.h>
#include <stdio.h>
void* server_thread(void* arg) {
    server_main();
    return NULL;
}

void* client_thread(void* arg) {
    client_main();
    return NULL;
}
int main(int argc, char *argv[]) {
    pthread_t server_tid, client_tid;

    
    if (pthread_create(&server_tid, NULL, server_thread, NULL) != 0) {
        fprintf(stderr, "Failed to create server thread\n");
        return 1;
    }

    
    if (pthread_create(&client_tid, NULL, client_thread, NULL) != 0) {
        fprintf(stderr, "Failed to create client thread\n");
        return 1;
    }

    pthread_join(server_tid, NULL);
    pthread_join(client_tid, NULL);

    return 0;
}