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
    printf("errno: %s", strerror(errno));
  }
}

int server_handshake( int * a) {
  int WKP;
  char * PP_name = malloc(sizeof(pid_t));
  if (mkfifo("weegee", 0644)) {
    printf("Oops! Something went wrong.\n");
    return -1;
  }
  else
    printf("[SERVER] made WKP. weegee\n");


  printf("[SERVER] waiting for connection on weegee..\n");
  
  WKP = open("weegee", O_RDONLY); //blocks here

  read(WKP, PP_name, sizeof(pid_t));
  
  printf("[SERVER] received client msg: %s\n", PP_name);
  
  //close WKP
  closePipeByName("weegee");
  printf("[SERVER] closed weegee");
  int PP;
  PP = open(PP_name, O_WRONLY);
  write(PP, "connected!", 11);

  free(PP_name);
  
  
  return 0;
}

int client_handshake( int * a ) {
  int WKP;
  int PP;
  char * PP_name = malloc(sizeof(pid_t));
  char serverMsg[1024];
  sprintf(PP_name, "%d", getpid());
  
  if (mkfifo(PP_name, 0644)) {
    printf("Oops!\n");
    return -1;
  }
  else
    printf("[CLIENT] made pp. pp_name: %s\n", PP_name);

  printf("[CLIENT] connecting to weegee\n");
  WKP = open("weegee", O_WRONLY); //blocks here

  printf("[CLIENT] connected weegee. %d\n", WKP);
  write(WKP, PP_name, sizeof(PP_name));
  printf("[CLIENT] wrote to weegee: %s\n", PP_name);
  
  PP = open(PP_name, O_RDONLY);

  read(PP, serverMsg, 11);

  closePipeByName(PP_name);
  free(PP_name);

  
  
  return 0;
}


//  int fds[2];
//  
//  pipe( fds );
//
//  
//  int f = fork();
//  if ( f == 0 ) {
//    close(fds[WRITE]);
//
//    printf("[child] listening\n");
//    char s[20];
//    //int x;    
//    read( fds[READ], s, sizeof(s) );
//    printf("[child] got: %s\n", s);
//  }
//  else {
//    close(fds[READ]);
//    
//    printf("[parent] sleeping\n");
//    sleep(5);    
//    write( fds[WRITE], "hello there", 12 );    
//  }
//  return 0;

