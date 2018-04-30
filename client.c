#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <arpa/inet.h>


#include "common.h"

int main(int argc, char const *argv[]) {
  int client_FD;
  char server_ip[16];
  char name[255];
  memset(&name, 0, sizeof name);
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9302);
  sprintf(server_ip,"%s",argv[1]);

  server_address.sin_addr.s_addr = inet_addr(server_ip);

  client_FD=socket(AF_INET,SOCK_STREAM,0);

  if ( 0 > connect(client_FD,(struct sockaddr *) &server_address ,sizeof(server_address)) )
    std::cout <<"Conncetion failed"<<std::endl;
//Üdvözlés
    char server_response[256];
   recv(client_FD,&server_response,sizeof(server_response),0);
   std::cout << server_response << std::endl;
   std::cin >> name;
   send(client_FD,name,sizeof(name),0);
//Üdvözlés vége

std::vector<Card> players_cards;
while(1){
   recv(client_FD,&server_response,sizeof(server_response),0);
    std::cout << server_response << std::endl;
    int card_id;
     sscanf(server_response, "%d", &card_id);
      find_cards(players_cards,card_id);

    recv(client_FD,&server_response,sizeof(server_response),0);
    std::cout << server_response << std::endl;
    sscanf(server_response, "%d", &card_id);
    find_cards(players_cards,card_id);
    show_cards(players_cards);

  break;
}






    close(client_FD);
  return 0;
}
