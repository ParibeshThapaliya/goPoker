#include "client.h"
#include "server.h"
#include "gui.h"

int main(int argc, char *argv[]) {
    // Call client_main, server_main, and gui_main as necessary
    server_main();
    client_main();
    
    
    return 0;
}