#ifndef COMMON_H
#define COMMON_H


#include <string>
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <stdio.h>


class Card {
public:
  int id;
  std::string color;
  int card_val;
  std::string val;
// bool operator==(const int & id) const { return this->id == id;}
}  ;
 std::string colors []  = {"Tök","Makk","Piros","Zöld"};
 std::string vals[] = {"Hét","Nyolc","Kilenc","Tíz","Alsó","Felső","Király","Ász"};



void make_deck (std::vector<Card>& _cards){
        int j = 0;
  for(int i=0; i < _cards.size();i++){

        _cards[i].id = i;

          if ((i%8)==0 && i >0)
            j++;
        _cards[i].color = colors[j];
        _cards[i].val = vals[i%8];

        if(  _cards[i].val == "Ász")
              _cards[i].card_val = 11;
              else if (_cards[i].val == "Alsó" )
              _cards[i].card_val = 2;
              else if (_cards[i].val == "Felső" )
              _cards[i].card_val = 3;
              else if (_cards[i].val == "Király" )
              _cards[i].card_val = 4;
              else if (_cards[i].val == "Tíz" )
              _cards[i].card_val = 10;
              else if (_cards[i].val == "Kilenc")
              _cards[i].card_val = 9;
              else if (_cards[i].val == "Nyolc")
              _cards[i].card_val = 8;
              else if (_cards[i].val == "Hét")
              _cards[i].card_val = 7;

  }

}
int myrandom (int i) { return std::rand()%i;}
std::vector<Card>  shuffle_deck(std::vector<Card> _cards){
  std::random_shuffle ( _cards.begin(), _cards.end(),myrandom );

  return _cards;

}

void show_deck(std::vector<int> &v,const std::vector<Card> &_cards){

for(int j = 0; j<v.size();j++)
for(int i =0;i<_cards.size();i++)
  {
    if(v[j] == _cards[i].id){
    std::cout << "=======================" << std::endl;

    std::cout << _cards[i].id << std::endl;
    std::cout << _cards[i].color << std::endl;
    std::cout << _cards[i].card_val << std::endl;
    std::cout << _cards[i].val << std::endl;
  }
  }

}

void show_deck(std::list<Card> & _cards){

for(std::list<Card>::iterator  i = _cards.begin(); i!=_cards.end();i++){

    std::cout << "=======================" << std::endl;

    std::cout << i->id << std::endl;
    std::cout << i->color << std::endl;
    std::cout << i->card_val << std::endl;
    std::cout << i->val << std::endl;
  }


}

void show_hand( std::vector<int>  hand,std::vector<Card> &cards) {

int sum = 0;
  for(int i = 0; i< hand.size();i++){
    for(int j = 0; j < cards.size();j++){
      if(hand[i] == cards[j].id){
    std::cout << cards[j].color << "  " << cards[j].val << " | ";
    sum+=cards[j].card_val;
}
  }

  }
    std::cout << "összesen: "<< sum <<std::endl;

}

int sum( std::vector<int>  hand, std::vector<Card> &cards) {

int sum = 0;
  for(int i = 0; i< hand.size();i++){
    for(int j = 0; j < cards.size();j++){
      if(hand[i]==cards[j].id)
      sum+=cards[j].card_val;
      }
  }
    return sum;
}

int who_won (std::vector<int>  &hand1,std::vector<int> &hand2,std::vector<Card> &cards){

      if((sum(hand1,cards) < 22 && sum(hand2,cards) > 21))
      return 1;
      if((sum(hand2,cards) < 22 && sum(hand1,cards) > 21))
      return 2;
      if(sum(hand1,cards) > sum(hand2,cards) )
      return 1;
      else if(sum(hand1,cards) < sum(hand2,cards) || (sum(hand2,cards) < 22 && sum(hand1,cards) > 22) )
      return 2;
      else if((sum(hand1,cards) == sum(hand2,cards)))
      return 0;
      else
      return -1;

}

void give_cards(int client_FD, std::vector<int> &client_deck,std::list<Card> & dealer_list){
      char server_ans [50];
     sprintf(server_ans,"%d",dealer_list.front().id );
     client_deck.push_back(dealer_list.front().id);
     dealer_list.pop_front();
     send(client_FD,server_ans,sizeof(server_ans),0);
    // std::cout<<server_ans<<std::endl;

     }

void recv_cards(int server_FD, std::vector<int>&client_deck){
  int card_id;
    char server_ans [50];
  recv(server_FD,&server_ans,sizeof(server_ans),0);
  sscanf(server_ans, "%d", &card_id);
  client_deck.push_back(card_id);
  // std::cout<<server_ans<<std::endl;
}




#endif
