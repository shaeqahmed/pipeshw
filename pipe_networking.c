#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "pipe_networking.h"

// Please note that all calls to sleep() are for demo of server&client purposes only 

int server_handshake(int * clientfd) {
  // STEP #1 - make the wellknownpipe
  printf("[SERVER] Making well known pipe...\n");
  mkfifo(wkp, 0644);
  // STEP #2 - make the wellknownpipe
  printf("[SERVER] Waiting for a client to connect...\n");
  *clientfd = open(wkp, O_RDONLY);
  // STEP #6 - recieve the client message and remove the wkp
  char clientmsg[MESSAGE_BUFFER_SIZE];
  read(*clientfd, clientmsg, MESSAGE_BUFFER_SIZE);
  sleep(5);
  printf("[SERVER] Received private FIFO name %s.\n", clientmsg);
  unlink(wkp);
  sleep(2);
  // STEP#7 - send message to client after connecting to clientfifo
  int clientfifo = open(clientmsg, O_WRONLY);
  printf("[SERVER] Connected to client FIFO %s.\n", clientmsg);
  char servermsg[MESSAGE_BUFFER_SIZE];
  strcpy(servermsg, servergreet);
  write(clientfifo, servermsg, strlen(servermsg));
  sleep(3);
  printf("[SERVER] Sent message to client.\n");
  // STEP#9 - get confirmation from client
  char clientverification[MESSAGE_BUFFER_SIZE];
  read(*clientfd, clientverification, MESSAGE_BUFFER_SIZE);
  sleep(2);
  printf("[SERVER] Received client verification: %s\n", clientverification);

  return clientfifo;//write
}

int client_handshake(int * serverfd) {

  // STEP#3 - make the private (client) fifo
  char clientfifoname[MESSAGE_BUFFER_SIZE];
  sprintf(clientfifoname, "%d", getpid()); //the private fifo name
  printf("[CLIENT] Created private FIFO %s.\n", clientfifoname);
  mkfifo(clientfifoname, 0644);
  sleep(3);
  // STEP#4 - connect to wkp and send private fifo name
  *serverfd = open(wkp, O_WRONLY);
  write(*serverfd, clientfifoname, strlen(clientfifoname));
  printf("[CLIENT] Connected to wkp and sent private FIFO name %s!\n", clientfifoname);
  sleep(3);
  // STEP#5 - wait for a server connection
  printf("[CLIENT] Waiting for server response...\n");
  int clientfifo = open(clientfifoname, O_RDONLY);
  // STEP#8 - get servermsg and then remove the private client fifo
  char servermsg[MESSAGE_BUFFER_SIZE];
  *servermsg = '\0';
  read(clientfifo, servermsg, MESSAGE_BUFFER_SIZE);
  sleep(4);
  printf("[CLIENT] Received server message: %s\n", servermsg);
  sleep(2);
  unlink(clientfifoname);
  // STEP#9 - send confirmation msg to serrver
  char clientverification[MESSAGE_BUFFER_SIZE];
  strcpy(clientverification, clientgreet);
  write(*serverfd, clientverification, strlen(clientverification));
  printf("[CLIENT] Sent message to server.\n");
  sleep(4);
  printf("[CLIENT] Connection established with server.\n");
  return clientfifo;//read
}
