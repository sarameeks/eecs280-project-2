#include "Pack.hpp"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on. 
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  // NOTE: The pack is initially full, with no cards dealt.
Pack::Pack() {

    int count = 0;
     for (int s = SPADES; s <= DIAMONDS; ++s) {
        Suit suit = static_cast<Suit>(s);

            for (int r = NINE; r <= ACE; r++) {
            Rank rank = static_cast<Rank>(r);
            Card card_input;    
            card_input = Card(rank, suit);
            cards[count] = card_input;
            count++;
     }
     }
    next = 0;
    
}


// REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  // NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(istream& pack_input) {

    for (int i = 0; i < PACK_SIZE; i++) {
        pack_input >> cards[i];
    }
    next = 0;

}


  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {

    Card card_temp = cards[next];
    next++;
    return card_temp;

}


// EFFECTS: Resets next index to the first card in the Pack.
void Pack::reset() {

    next = 0;

}

// EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    
    int HALF_SIZE = PACK_SIZE / 2;
    array<Card, 24UL> temp_pack;
    int TIMES_SHUFFLED = 7;

    for (int j = 0; j < TIMES_SHUFFLED; j++) {
    for (int i = 0; i < HALF_SIZE; i++) {
    temp_pack[2 * i]     = cards[HALF_SIZE + i]; 
    temp_pack[2 * i + 1] = cards[i]; 
    }
    cards = temp_pack;
}
    next = 0;
}

// EFFECTS: Returns true if there are no more cards left in the Pack.
bool Pack::empty() const {

    if (next == PACK_SIZE) {
        return true;
    }
    else if (next < PACK_SIZE) {
        return false;
    }
    return false;
    
}