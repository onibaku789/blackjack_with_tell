#ifndef COMMON_H
#define COMMON_H

#include <iostream>
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
 bool operator==(const int & id) const { return this->id == id;}
}  ;
 std::string colors []  = {"Tök","Makk","Piros","Zöld"};
 std::string vals[] = {"Hét","Nyolc","Kilenc","Tíz","Alsó","Felső","Király","Ász"};


std::vector<Card> cards (32);

void make_deck (std::vector<Card>& _cards){

  for(int i=0; i < _cards.size();i++){

        _cards[i].id = i;


        _cards[i].color = colors[i%4];
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

void show_deck(const std::vector<Card> &_cards){

for(int i =0;i<_cards.size();i++)
  {
    std::cout << "=======================" << std::endl;

    std::cout << _cards[i].id << std::endl;
    std::cout << _cards[i].color << std::endl;
    std::cout << _cards[i].card_val << std::endl;
    std::cout << _cards[i].val << std::endl;

  }

}

void show_cards(const std::vector<Card> & _cards){


  for(int i =0;i<_cards.size();i++)
    std::cout << _cards[i].color << "  " << _cards[i].val << " | ";

    std::cout <<std::endl;

}
void find_cards(std::vector<Card> &players_cards,int card_id){

for(int i = 0; i<cards.size();i++){
  if(card_id==cards[i].id){
    players_cards.push_back(cards[i]);
    std::cout<< i<<std::endl;
        }
    }

}



#endif
