#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <vector>


typedef struct Card {
  int id;
  char* color;
  int card_val;
  char* val;
} Card ;
 char * colors []  = {"Tök","Makk","Piros","Zöld"};
char * vals[] = {"Hét","Nyolc","Kilenc","Tíz","Alsó","Felső","Király","Ász"};


std::vector<Card> _cards (32);

void make_deck (std::vector<Card>& _cards){

  for(int i=0; i < _cards.size();i++){

        _cards[i].id = i;


        _cards[i].color = colors[i%4];
          _cards[i].val = vals[i%8];

        if(  _cards[i].val == "Ász")
              _cards[i].card_val = 11;
        else if(  _cards[i].val == "Alsó" || _cards[i].val == "Felső" || _cards[i].val == "Király" ||_cards[i].val == "Tíz" )
        _cards[i].card_val = 10;
        else if (_cards[i].val == "Kilenc")
        _cards[i].card_val = 9;
        else if (_cards[i].val == "Nyolc")
          _cards[i].card_val = 8;
        else if (_cards[i].val == "Hét")
                _cards[i].card_val = 7;



  }

}



#endif
