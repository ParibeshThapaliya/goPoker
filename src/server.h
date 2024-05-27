
#define MESSAGE_SIZE 4096
#define MAX_NAME_LEN 100

struct Client {
    int socket;
    char name[MAX_NAME_LEN];
    struct Client *next;
};
void server_main();
extern struct Client *g_clients;

/**
 * @brief print all client
 */
void print_all_clients();

/**
 * @brief create a server socket
 */
int create_server(unsigned short port);

/**
 * @brief find client by name, return NULL if not exist
 */
struct Client* find_client_by_name(const char *name);

/**
 * @brief find client by socket, return NULL if not exist
 */
struct Client* find_client_by_socket(int socket);

/**
 * @brief get client name by socket, return 1 if success, return 0
 *      if not exist
 */
int get_name_by_socket(int socket, char *name);

/**
 * @brief add a client to client list
 */
void add_client(int socket, const char *name);

/**
 * @brief remove a client from client list by name
 */
void remove_client_by_name(const char *name);

/**
 * @brief remove a client from client list by socket
 */
void remove_client_by_socket(int socket);

/**
 * @brief send a message to a client
 */
int send_to_client(const char *name, const void *buffer, int count);