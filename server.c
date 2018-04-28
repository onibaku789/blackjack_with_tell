
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>

#include <netinet/in.h>

#include <unistd.h>

#include "common.h"


int main(int argc, char const *argv[]) {
  int server_FD, client1_FD,client2_FD;
  char server_message [256] ="kysMonkaOmegakys";

  server_FD=socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9302);
  server_address.sin_addr.s_addr = INADDR_ANY;

  bind(server_FD,(struct sockaddr*) &server_address,sizeof(server_address));
  std::cout << "Bind rdy"<<std::endl;

  listen(server_FD,5);
  std::cout << "FBI's van cosplay"<<std::endl;

  std::cout << "awating player1"<<std::endl;
  client1_FD = accept(server_FD,NULL,NULL );
  std::cout << "awating player2"<<std::endl;
  client2_FD = accept(server_FD,NULL,NULL );
  send(client1_FD,server_message,sizeof(server_message),0);
  send(client2_FD,server_message,sizeof(server_message),0);

  close(server_FD);







  return 0;
}
