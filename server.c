
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>

#include "common.h"


int main(int argc, char const *argv[]) {
  int server_FD, client1_FD,client2_FD;
  char welcome_msg [30] ="Üdvözlet, add meg a neved: ";
  char client1_ans[255];
  char client2_ans[255];

    memset(&client1_ans, 0, sizeof client1_ans);
    memset(&client2_ans, 0, sizeof client2_ans);

  server_FD=socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9302);
  server_address.sin_addr.s_addr = INADDR_ANY;

  bind(server_FD,(struct sockaddr*) &server_address,sizeof(server_address));
  std::cout << "Bind rdy"<<std::endl;

  listen(server_FD,5);
  std::cout << "FBI van cosplay"<<std::endl;

  std::cout << "awating player1"<<std::endl;
  client1_FD = accept(server_FD,NULL,NULL );
  std::cout << "awating player2"<<std::endl;
  client2_FD = accept(server_FD,NULL,NULL );

  //Üdvözlés
  send(client1_FD,welcome_msg,sizeof(welcome_msg),0);
  send(client2_FD,welcome_msg,sizeof(welcome_msg),0);
  recv(client1_FD,&client1_ans,sizeof(client1_ans),0);
  recv(client2_FD,&client2_ans,sizeof(client2_ans),0);

  std::string client1_name (client1_ans);
  std::string client2_name(client2_ans);

  std::cout << client1_name << " " << client2_name<<std::endl;
  //Üdvözlés vége

  int client1_deck[32];
  int client2_deck[32];
  memset(&client1_deck, 0, sizeof client1_deck);
  memset(&client2_deck, 0, sizeof client2_deck);

  make_deck(cards);

  std::vector<Card> shuffled_deck(shuffle_deck(cards));
  int i = 0;
  while(1){
    char players_cards[255];
        sprintf(players_cards,"%ld",shuffled_deck[0].id );
        send(client1_FD,players_cards,sizeof(players_cards),0);



        sprintf(players_cards,"%ld",shuffled_deck[1].id );
        send(client1_FD,players_cards,sizeof(players_cards),0);

        sprintf(players_cards,"%ld",shuffled_deck[2].id );
        send(client2_FD,players_cards,sizeof(players_cards),0);



        sprintf(players_cards,"%ld",shuffled_deck[3].id );
        send(client2_FD,players_cards,sizeof(players_cards),0);
        break;
  }













  close(server_FD);

  return 0;
}
