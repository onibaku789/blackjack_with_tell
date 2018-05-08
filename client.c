#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <arpa/inet.h>
#include <list>


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
std::vector<Card> cards (32);
make_deck(cards);

std::vector<int> player_hand;
std::vector<int> player2_hand;

while(1){
  char player_ans[255];
  int card_id;
  memset(&player_ans, 0, sizeof player_ans);

   recv(client_FD,&server_response,sizeof(server_response),0);
   sscanf(server_response, "%d", &card_id);
   player_hand.push_back(card_id);

   show_hand(player_hand,cards);

while(1){

  memset(&server_response, 0, sizeof server_response);

   if( 15 > sum(player_hand,cards)){
    recv(client_FD,&server_response,sizeof(server_response),0);
    sscanf(server_response, "%d", &card_id);
    player_hand.push_back(card_id);
    show_hand(player_hand,cards);

    }
    else if(sum(player_hand,cards) < 22){
      std::cout<< "Lapkérés:k , Megállás:m "<<std::endl;
      std::cin >> player_ans;
      send(client_FD,player_ans,sizeof(player_ans),0);
      if( strcmp(player_ans, "k") == 0){
        std::cout << "Lapot kértem" << std::endl;
      recv(client_FD,&server_response,sizeof(server_response),0);
      sscanf(server_response, "%d", &card_id);
      player_hand.push_back(card_id);
      show_hand(player_hand,cards);
      }
      else if( strcmp(player_ans, "m")==0 ){

      std::cout << "Nem lapot kértem"<< std::endl;
      break;
        }
      }
      else
      break;

}

      while(1){
        recv(client_FD,&server_response,sizeof(server_response),0);

        if(strcmp(server_response,"1") == 0){
      memset(&server_response, 0, sizeof server_response);

      int player2_hand_size,player2_card=0;
      recv(client_FD,&server_response,sizeof(server_response),0);
      sscanf(server_response,"%d",&player2_hand_size );

      for(int i = 0; i < player2_hand_size; i++ ){


        recv(client_FD,&server_response,sizeof(server_response),0);
        sscanf(server_response,"%d",&player2_card );
        player2_hand.push_back(player2_card);

        }


        recv(client_FD,&server_response,sizeof(server_response),0);

        while(1){
          recv(client_FD,&server_response,sizeof(server_response),0);
            if(strcmp(server_response,"2") == 0){
              std::cout << "A másik játékos lapjai: " << std::endl;
              show_hand(player2_hand,cards);
              std::cout << "A saját lapjaid: " << std::endl;
              show_hand(player_hand,cards);


if (who_won(player_hand,player2_hand,cards) == 1)
    std::cout << "Nyertél :)"<<std::endl;
else if(who_won(player_hand,player2_hand,cards) == 2)
    std::cout << "Vesztettél :("<<std::endl;
else if(who_won(player_hand,player2_hand,cards) == 0)
    std::cout << "Döntetlen ??" << std::endl;
else
std::cout << "-1" << std::endl;
break;
  }
  }
  break;

}
}



break;

}

    close(client_FD);
  return 0;
}
