#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int closePipeByName(char * pipeName){
  char * command[2];
  command[0] = "rm";
  command[1] = pipeName;
  return execvp(command[0], command);
  
}

int server_handshake( int * a) {
  int WKP;
  char * PP_name = malloc(sizeof(pid_t));
  if (mkfifo("weegee", 0644)) {
    printf("Oops! Something went wrong.\n");
    return -1;
  }
  WKP = open("weegee", O_RDONLY); //blocks here

  read(WKP, PP_name, sizeof(pid_t));

  //close WKP
  int isClosed = closePipeByName("weegee");
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
  printf("pp_name: %s\n", PP_name);
  
  if (mkfifo(PP_name, 0644)) {
    printf("Oops!\n");
    return -1;
  }


  WKP = open("weegee", O_WRONLY); //blocks here
  write(WKP, PP_name, sizeof(PP_name));
  
  PP = open(PP_name, O_RDONLY);

  read(PP, serverMsg, 11);

  int isClosed = closePipeByName(PP_name);
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

