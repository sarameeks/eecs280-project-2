#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
//EFFECTS returns the Rank corresponding to str, for example "Two" -> TWO
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank 
    = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
//EFFECTS returns the Suit corresponding to str, for example "Clubs" -> CLUBS
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=


/////////////// Write your implementation for Card below ///////////////

// Default constructor
Card::Card() {
    rank = TWO;
    suit = SPADES;
      //EFFECTS Initializes Card to the Two of Spades
}

// Value constructor
Card::Card(Rank rank_in, Suit suit_in) {
    //EFFECTS Initializes Card to specified rank and suit
  rank = rank_in;
  suit= suit_in;
}

Rank Card::get_rank() const {
  return rank;
}

Suit Card::get_suit() const {
  return suit;
}

Suit Card::get_suit(Suit trump) const {
  
  if (is_left_bower(trump)) {
    return trump;
  }
  else
   return suit;
}
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit

bool Card::is_face_or_ace() const {
  if(rank == JACK || rank == QUEEN || rank == KING || rank == ACE)  
    return true;
  else
    return false;
}

bool Card::is_right_bower(Suit trump) const {
  //EFFECTS Returns true if card is the Jack of the trump suit
    if(rank == JACK && suit == trump)
      return true;
    else
      return false;
}

bool Card::is_left_bower(Suit trump) const {
    //EFFECTS Returns true if card is the Jack of the next suit
  if(rank == JACK && trump == HEARTS && suit == DIAMONDS) {
    return true;
  }
  else if(rank == JACK && trump == DIAMONDS && suit == HEARTS) {
    return true;
  }
  else if(rank == JACK && trump == CLUBS && suit == SPADES) {
    return true;
  }
  else if(rank == JACK && trump == SPADES && suit == CLUBS) {
    return true;
  }
  else 
    return false;
}

bool Card::is_trump(Suit trump) const {
    if (suit == trump || is_left_bower(trump)) 
      return true;
    else
      return false;
    // TODO: return true if card is trump suit or left bower
}

  //EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
  os << card.get_rank() << " of " << card.get_suit();
    return os;
}
//EFFECTS Reads a Card from a stream in the format "Two of Spades"

std::istream & operator>>(std::istream &is, Card &card) {
//EFFECTS Reads a Card from a stream in the format "Two of Spades"
  string of;
  is >> card.rank;
  is >> of;
  is >> card.suit;
    return is;
}
//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
//lhs left hand side carde
bool operator<(const Card &lhs, const Card &rhs) {
  if (lhs.get_rank() != rhs.get_rank()) {
        return lhs.get_rank() < rhs.get_rank();
    }
    return lhs.get_suit() < rhs.get_suit();
}
    // TODO: standard card comparison (rank first, then suit)

bool operator<=(const Card &lhs, const Card &rhs) {
  return (rhs < lhs || lhs == rhs);
}

bool operator>(const Card &lhs, const Card &rhs) {
  if (lhs.get_rank() != rhs.get_rank()) {
        return lhs.get_rank() > rhs.get_rank();
    }
    return lhs.get_suit() < rhs.get_suit();
}

bool operator>=(const Card &lhs, const Card &rhs) {
  return (lhs > rhs || lhs == rhs);
}

bool operator==(const Card &lhs, const Card &rhs) {
  return (lhs.get_rank() == rhs.get_rank());
}

bool operator!=(const Card &lhs, const Card &rhs) {
  return !(lhs == rhs);
}

Suit Suit_next(Suit suit) {
  if(suit == HEARTS) {
    return DIAMONDS;
  }
  else if(suit == DIAMONDS) {
    return HEARTS;
  }
  else if(suit == SPADES) {
    return CLUBS;
  }
  else if(suit == CLUBS) {
    return SPADES;
  }
  return HEARTS;
}

//true if a < b
bool Card_less(const Card &a, const Card &b, Suit trump) {
  
  bool a_is_left_bower = a.is_left_bower(trump);
  bool b_is_left_bower = b.is_left_bower(trump);

  bool a_is_right_bower = a.is_right_bower(trump);
  bool b_is_right_bower = b.is_right_bower(trump);

  bool a_is_trump = a.is_trump(trump);
  bool b_is_trump = b.is_trump(trump);

  int rank_a = a.get_rank();
  int rank_b = b.get_rank();

    //Both cards are trump:
    if (a_is_trump && b_is_trump) {

      //If a is the right bower:
      if (a_is_right_bower) 
            return false;
      //If b is the right bower:
      if (b_is_right_bower)
            return true;
      //If a is the left bower:
      if (a_is_left_bower)
            return false;
      //If b is the left bower:
      if (b_is_left_bower)
            return true;
      //Otherwise compare ordinary trump ranks
      else
        return (rank_a < rank_b);

    }

    //only a is trump
    else if(a_is_trump && !b_is_trump) {
      return false;
    }

    //only b is trump
    else if(b_is_trump && !a_is_trump) {
       return true;
    //Both non trump cards
    }
    else
      return (rank_a < rank_b);

  }

bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump) {

    //Determine the led suit from led_card
    int leading_suit = led_card.get_suit();

    //Determine whether a and b are trump
    bool a_is_trump = a.is_trump(trump);
    bool b_is_trump = b.is_trump(trump);

    //Determine whether a and b belong to the led suit, remeber the left bower
    bool a_is_leading_suit = (leading_suit == a.get_suit());
    bool b_is_leading_suit = (leading_suit == b.get_suit());

    int rank_a = a.get_rank();
    int rank_b = b.get_rank();

    bool a_is_left_bower = a.is_left_bower(trump);
    bool b_is_left_bower = b.is_left_bower(trump);

    bool a_is_right_bower = a.is_right_bower(trump);
    bool b_is_right_bower = b.is_right_bower(trump);

    // // CASE A: a is trump, b is NOT trump
    // if(a_is_trump && !b_is_trump)
    //         return false;
    // //CASE B: b is trump, a is NOT trump
    // else if(b_is_trump && !a_is_trump)
    //         return true;
    // //CASE C1: a follows the led suit, but b does NOT
    // else if(a_is_leading_suit && !b_is_leading_suit)
    //         return false;

    // // CASE C2: b follows the led suit, but a does NOT
    // else if (b_is_leading_suit && !a_is_leading_suit)
    //         return true;
    // }

    // STEP 4: Compare ranks
    //     If the function has not returned yet,
    //     both cards belong to the same category.

    //  CASE A: Both cards are trump
    //         Compare using trump ranking rules:
    //             Right bower > Left bower > Ace > King > Queen > 10 > 9.


    if (a_is_trump && b_is_trump) {
      //If a is the right bower:
      if (a_is_right_bower) 
            return false;
      //If b is the right bower:
      if (b_is_right_bower)
            return true;
      //If a is the left bower:
      if (a_is_left_bower)
            return false;
      //If b is the left bower:
      if (b_is_left_bower)
            return true;
      //Otherwise compare ordinary trump ranks
      else
        return (rank_a < rank_b);
    }

    //only a is trump
    else if(a_is_trump && !b_is_trump) {
      return false;
    }

    //only b is trump
    else if(b_is_trump && !a_is_trump) {
       return true;
    //Both non trump cards
    }

    else if (a_is_leading_suit && b_is_leading_suit) 
        return (rank_a < rank_b);

    else if (a_is_leading_suit && b_is_leading_suit && !b_is_trump && !a_is_trump)
        return (rank_a < rank_b);

    else
      return (rank_a < rank_b);

}
