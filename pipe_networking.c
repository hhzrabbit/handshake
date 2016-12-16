#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int server_handshake( int * a) {
  int WKP;
  if (mkfifo("weegee", 0644)) {
    printf("Oops! Something went wrong.\n");
    return -1;
  }
  WKP = open("weegee", O_RDONLY); //blocks here
  pid_t PP_name;
  read(WKP, &PP_name, sizeof(pid_t));
  int PP;
  PP = open(PP_name, O_WRONLY);
  write(PP, "connected!", 11);
  
  return 0;
}

int client_handshake() {
  int PP;
  if (mkfifo(getpid(), 0644)) {
    printf("Oops!\n");
    return -1;
  }

  int WKP;
  WKP = open("weegee", O_WRONLY); //blocks here
  write(pp, getpid(), sizeof(pid_t));
  int PP;
  PP = open(getpid(), O_RDONLY);
  char whatever[1024];
  read(PP, whatever, 11);
  
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
