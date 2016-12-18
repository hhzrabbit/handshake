#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "pipe_networking.h"

// Signal Handling
static void sighandler(int SIGNO) {
  if (SIGNO == SIGINT) {
    printf("\n[CLIENT] Closing...\n");
    char PP_name[16];
    snprintf(PP_name, 16, "%d", getpid());
    closePipeByName(PP_name);
    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);
  int to_server, from_server;

  from_server = client_handshake( &to_server );
  // printf("To Server: %d\tFrom Server: %d\n", to_server, from_server); // Debug

  char buffer[MESSAGE_BUFFER_SIZE];
  while (1) {
    printf("[CLIENT] Enter message: ");
    fgets( buffer, sizeof(buffer), stdin );
    if (buffer[strlen(buffer)-1] == '\n')
      buffer[strlen(buffer)-1] = 0;
    
    write( to_server, buffer, sizeof(buffer) );
    read( from_server, buffer, sizeof(buffer) );
    printf( "[CLIENT] Received: %s\n", buffer );
  }

  return 0;
}
