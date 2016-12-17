#define MESSAGE_BUFFER_SIZE 1024
#define servergreet "Nice to see you, client!" //msg
#define clientgreet "Facts, it's a pleasure to meet you, server!" // the response
#define wkp "wkp"
int server_handshake(int * client_fd);
int client_handshake(int * server_fd);
