#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int server_handshake( int * a) {
  int WKP;
  if (!(mkfifo("weegee", 0644)) { // Backwards, fix later
    printf("Oops!\n");
    return -1;
  }
  return 0;
}

int client_handshake() {
  int WKP;
  if (!(WKP = mkfifo("weegee", 0644))) {
    printf("Oops!\n");
    return -1;
  }
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