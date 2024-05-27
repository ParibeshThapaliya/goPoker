#include "client.h"
#include "server.h"
#include "GUI.h"

int main(int argc, char *argv[]) {
    client_main();
    server_main();
    
    return 0;
}