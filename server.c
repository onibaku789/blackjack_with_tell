
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <list>

#include "common.h"


int main(int argc, char const *argv[]) {
  int server_FD, client1_FD,client2_FD;
  char welcome_msg [30] ="Üdvözlet, add meg a neved: ";
  char client1_ans[255];
  char client2_ans[255];
  std::srand ( unsigned ( std::time(0) ) );

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

  std::vector<int> client1_deck;
  std::vector<int> client2_deck;


std::vector<Card> cards (32);

  make_deck(cards);



  while(1){
    char  server_ans[255];
    std::vector<Card> shuffled_deck(shuffle_deck(cards));
    std::list<Card> dealer_list;
    std::copy(shuffled_deck.begin(), shuffled_deck.end(), std::back_inserter( dealer_list ) );


        sprintf(server_ans,"%d",dealer_list.front().id );
        client1_deck.push_back(dealer_list.front().id);
        dealer_list.pop_front();

        send(client1_FD,server_ans,sizeof(server_ans),0);



        sprintf(server_ans,"%d",dealer_list.front().id );
        client2_deck.push_back(dealer_list.front().id);
        dealer_list.pop_front();

        send(client2_FD,server_ans,sizeof(server_ans),0);


     while(1){
       memset(&client1_ans, 0, sizeof client1_ans);
       memset(&server_ans, 0, sizeof server_ans);



       if (sum(client1_deck,cards) < 15 ){

          sprintf(server_ans,"%d",dealer_list.front().id );
          client1_deck.push_back(dealer_list.front().id);
          dealer_list.pop_front();
          send(client1_FD,server_ans,sizeof(server_ans),0);
          }
        else {
            recv(client1_FD,&client1_ans,sizeof(client1_ans),0);
            if(strcmp(client1_ans, "k")==0){
            sprintf(server_ans,"%d",dealer_list.front().id );
            client1_deck.push_back(dealer_list.front().id);
            dealer_list.pop_front();
            send(client1_FD,server_ans,sizeof(server_ans),0);
            }
            else   if( strcmp(client1_ans, "m")==0 || sum(client1_deck,cards) > 21)
              break;
          }

        }




        while(1){
          memset(&client2_ans, 0, sizeof client2_ans);
          memset(&server_ans, 0, sizeof server_ans);

          if (sum(client2_deck,cards) < 15 ){

             sprintf(server_ans,"%d",dealer_list.front().id );
             client2_deck.push_back(dealer_list.front().id);
             dealer_list.pop_front();
             send(client2_FD,server_ans,sizeof(server_ans),0);
             }
          else {
              recv(client2_FD,&client2_ans,sizeof(client2_ans),0);
              if(client2_ans == "k"){
              sprintf(server_ans,"%d",dealer_list.front().id );
              client2_deck.push_back(dealer_list.front().id);
              dealer_list.pop_front();
              send(client2_FD,server_ans,sizeof(server_ans),0);
               }
               else if( strcmp(client2_ans, "m")==0 || sum(client2_deck,cards) > 21)
                break;

           }
         }




      sprintf(server_ans,"%d",client2_deck.size() );
      send(client1_FD,server_ans,sizeof(server_ans),0);
      for(int i = 0; i < client2_deck.size(); i++ ){
      sprintf(server_ans,"%d",client2_deck[i] );
      send(client1_FD,server_ans,sizeof(server_ans),0);
      }

      sprintf(server_ans,"%d",client1_deck.size() );
      send(client2_FD,server_ans,sizeof(server_ans),0);
      for(int j = 0; j < client1_deck.size(); j++ ){
      sprintf(server_ans,"%d",client1_deck[j] );
      send(client2_FD,server_ans,sizeof(server_ans),0);
      }






      break;
  }













  close(server_FD);

  return 0;
}
