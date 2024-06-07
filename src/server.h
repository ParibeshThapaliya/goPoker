
#define MESSAGE_SIZE 4096
#define MAX_NAME_LEN 100

struct Client {
    int socket;
    char name[MAX_NAME_LEN];
    struct Client *next;
};

int startServer();

int Socket