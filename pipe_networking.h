#define MESSAGE_BUFFER_SIZE 1024
#define HANDSHAKE_BUFFER_SIZE 512
#define servergreet "Nice to see you, client!" //msg
#define clientgreet "Facts, it's a pleasure to meet you, server!" // the response
#define wkp "wkp"



int server_handshake(int * client_fd);
int client_handshake(int * server_fd);
int server_handshake(int *);
int client_handshake(int *);
int server_handshake1 (char *buffer);
int server_handshake2 (char *buffer, int from_client);