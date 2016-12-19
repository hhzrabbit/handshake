#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

void closePipeByName(char * pipeName){
  int f = fork();
  if (f == 0){
    char * command[3];
    command[0] = "rm";
    command[1] = pipeName;
    command[2] = 0;
    int status = execvp(command[0], command);
    printf("errno: %s", strerror(errno)); // Debugging
  }
}

int server_handshake( int * a ) {
  int WKP;
  char PP_name[16];

  // Creating WKP
  if (mkfifo("weegee", 0644)) {
    printf("Oops! Something went wrong.\n");
    return -1;
  }
  else
    printf("[SERVER] Created WKP (weegee).\n");

  // Listening
  printf("[SERVER] Waiting for connection on weegee...\n");
  WKP = open("weegee", O_RDONLY); //blocks here
  read(WKP, PP_name, sizeof(PP_name));
  
  // Connection Established, Removing WKP
  printf("[SERVER] Received Client Message: %s\n", PP_name);
  closePipeByName("weegee");
  printf("[SERVER] Closed WKP.\n");

  // Establish Connection to PP
  int PP = open(PP_name, O_WRONLY);
  write(PP, "Connected!", 11);

  *a = WKP; // from_client
  return PP; // to_client
}

int client_handshake( int * a ) {
  int WKP; // WKP file descriptor
  int PP; // PP file descriptor
  char PP_name[16];
  char serverMsg[32];
  snprintf(PP_name, 16, "%d", getpid());

  // Creating PP
  if (mkfifo(PP_name, 0644)) {
    printf("Oops!\n");
    return -1;
  }
  else
    printf("[CLIENT] Created PP (%s)\n", PP_name);

  // Connecting to WKP
  printf("[CLIENT] Connecting to Server (weegee).\n");
  WKP = open("weegee", O_WRONLY); //blocks here

  
  // Connected to WKP, Send Details of PP
  if (WKP != -1) {
    printf("[CLIENT] Connected to Server.\n");
    write(WKP, PP_name, sizeof(PP_name));
    printf("[CLIENT] wrote to weegee: %s\n", PP_name);
  
    // Waiting For Server to Establish Connection with PP
    PP = open(PP_name, O_RDONLY);
    
    // Connection Established, Closing PP
    read(PP, serverMsg, 11);
    printf("[CLIENT] Received: %s\n", serverMsg);
    closePipeByName(PP_name);
    printf("[CLIENT] Closed PP.\n");
    
    *a = WKP; // to_server
  }
  else {
    printf("[CLIENT] Error: Server not found (weegee)\n");
    return -1;
  }
  return PP; // from_server
}
