#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "pipe_networking.h"

void process( char * s );

// Signal Handling
static void sighandler(int SIGNO) {
  if (SIGNO == SIGINT) {
    printf("\n[SERVER] Closing...\n");
    closePipeByName("weegee");
    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);
  int to_client, from_client;
  
  to_client = server_handshake( &from_client );
  // printf("To Client: %d\tFrom Client: %d\n", to_client, from_client); // Debug

  char buffer[MESSAGE_BUFFER_SIZE];
  while (1) {
    read(from_client, buffer, sizeof(buffer)); // Read from Client
    printf( "[SERVER] Received: %s\n", buffer );
    process( buffer ); // Process data
    write(to_client, buffer, sizeof(buffer)); // Write to Client
  }

  return 0;
}

void process( char * s ) {
  while ( *s ) {
    *s = (*s - 'a' + 13) % 26 + 'a';
    s++;
  }
}
