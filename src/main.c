#include "client.h"
#include "server.h"
#include "GUI.h"

int main(int argc, char *argv[]) {
    server_main();
    client_main();
    return 0;
}