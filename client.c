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
  int server_FD;
  char server_ip[16];
  char name[255];
  memset(&name, 0, sizeof name);
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9302);
  sprintf(server_ip,"%s",argv[1]);

  server_address.sin_addr.s_addr = inet_addr(server_ip);

  server_FD=socket(AF_INET,SOCK_STREAM,0);

  if ( 0 > connect(server_FD,(struct sockaddr *) &server_address ,sizeof(server_address)) )
    std::cout <<"Conncetion failed"<<std::endl;
//Üdvözlés
    char server_response[256];
   recv(server_FD,&server_response,sizeof(server_response),0);
   std::cout << server_response << std::endl;
   std::cin >> name;
   send(server_FD,name,sizeof(name),0);
//Üdvözlés vége
std::vector<Card> cards (32);
make_deck(cards);

std::vector<int> player_hand;
std::vector<int> player2_hand;
char client_ans[255];
char server_ans[255];
while(1){

  recv_cards(server_FD, player_hand);
  show_hand(player_hand,cards);

  while(sum(player_hand,cards) < 15){
    recv_cards(server_FD, player_hand);
    show_hand(player_hand,cards);
  }
  while(sum(player_hand,cards) < 22){
std::cout << "Lapkérés:k Megtartás:m"<<std::endl;
std::cin >> client_ans;
send(server_FD,client_ans,sizeof client_ans,0 );
if(strcmp(client_ans,"k")==0)
recv_cards(server_FD, player_hand);
if(strcmp(client_ans,"m")==0)
break;
show_hand(player_hand,cards);
}
  show_hand(player_hand,cards);
  int player2_hand_size = 0,card_id=0;
  recv(server_FD,&server_ans,sizeof(server_ans),0);
  sscanf(server_ans, "%d", &player2_hand_size);
for(int i = 0; i<player2_hand_size;i++){
  recv(server_FD,&server_ans,sizeof(server_ans),0);
  sscanf(server_ans, "%d", &card_id);
  player2_hand.push_back(card_id);
}

recv(server_FD,&server_ans,sizeof(server_ans),0);
if(strcmp(server_ans,"hirdetes")==0){
std::cout << "az ellenfeled kártyái" << std::endl;
show_hand(player2_hand,cards);
std::cout << "a te kártyáid" << std::endl;
show_hand(player_hand,cards);

//std::cout << who_won(player_hand,player2_hand,cards)<<" " <<sum(player_hand,cards)<< sum(player2_hand,cards) << std::endl;
if(who_won(player_hand,player2_hand,cards) == 0)
  std::cout << "döntetlen" << std::endl;
else if(who_won(player_hand,player2_hand,cards)==1)
  std::cout << "nyertél" << std::endl;
else if(who_won(player_hand,player2_hand,cards)==2)
  std::cout << "vesztettél" << std::endl;
}



break;
}




    close(server_FD);
  return 0;
}
