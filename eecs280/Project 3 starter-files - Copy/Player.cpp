#include "Player.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
////////////////////////////////////////////////////////////////////
class SimplePlayer : public Player {
private:
    std::string name;
    std::vector<Card> hand;

public:

    SimplePlayer(const std::string &name_in) 
        : name(name_in) {}

    //EFFECTS returns player's name 
    const std::string & get_name() const override {
        return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }

    //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.

  
    bool make_trump(const Card &upcard, 
                    bool is_dealer,
                    int round, 
                    Suit &order_up_suit) const override {
        // TODO: Implement Simple player make_trump strategy
        // Remember: Simple player should NOT print any output.
        int points = 0;
        int enough_matching_trump = 2;

        //get upcard color
        char upcard_color;
        char hand_color;
        char red = 'r';
        char black = 'b';
        if(upcard.get_suit() == HEARTS || upcard.get_suit() == DIAMONDS) 
          upcard_color = red;
        else if(upcard.get_suit() == SPADES || upcard.get_suit() == CLUBS)
          upcard_color = black;

        if (round == 1) {
          for (int i = 0; i < MAX_HAND_SIZE; i++) {
            if (hand[i].is_face_or_ace() && hand[i].is_trump(
              upcard.get_suit())) {
            points++;
          }
        }

          if (points >= enough_matching_trump) 
          order_up_suit = upcard.get_suit();
            return true;
        }

        else if (round == 2) {

          for (int i = 0; i < MAX_HAND_SIZE; i++) {

            if(hand[i].get_suit() == HEARTS || hand[i].get_suit() == DIAMONDS) 
              hand_color = red;
            else if(hand[i].get_suit() == SPADES || hand[i].get_suit() == CLUBS)
              hand_color = black;

            if (hand[i].is_face_or_ace() && 
            hand_color == upcard_color
            && hand[i].get_suit() != upcard.get_suit()) 
            points++;
          }


          if (points >= enough_matching_trump) {
            order_up_suit = Suit_next(upcard.get_suit());
            return true;
          }
        }
        return false;
      }
        
    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and 
    //removes one card from hand.
    void add_and_discard(const Card &upcard) override {
        
      Card lowest = upcard;
      int lowest_hand_position = 10;
      for (int i = 0; i < MAX_HAND_SIZE; i++) {
        if (Card_less(hand[i], lowest, upcard.get_suit())) {
            lowest = hand[i];
            lowest_hand_position = i;
        }
      }
      if (lowest != upcard) {
        hand[lowest_hand_position] = upcard;
      }
  }

    //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  
    Card lead_card(Suit trump) override {

      assert(!hand.empty());
      std::vector<Card> trump_hand;
      std::vector<Card> non_trump_hand;
      Card lowest = hand[0];
      Card highest = hand[0];
      Card playing_card = hand[0];
      int highest_hand_position = 10;


      //Seperates deck into trump and non-trump cards
      for (int i = 0; i < MAX_HAND_SIZE; i++) {
        if(hand[i].get_suit() == trump)
          trump_hand.push_back(hand[i]);
        else
          non_trump_hand.push_back(hand[i]);
      }

      //If all cards are trump, play the lowest card
      if(trump_hand.size() == MAX_HAND_SIZE) {
        int lowest_hand_position = 10;
        for (int i = 0; i < MAX_HAND_SIZE; i++) {
          if (Card_less(hand[i], lowest, trump)) {
              lowest = hand[i];
              lowest_hand_position = i;
          }
        playing_card = hand[lowest_hand_position];
        hand.erase(hand.begin() + lowest_hand_position);
      }
      }

      //If there is at least one non trump card, play the highest card in hand
      else {
        for (int i = 0; i < non_trump_hand.size(); i++) {
        highest = non_trump_hand[0];
        if (!Card_less(non_trump_hand[i], highest, trump)) {
            highest = hand[i];
            highest_hand_position = i;
        }
        }
        playing_card = hand[highest_hand_position];
        hand.erase(hand.begin() + highest_hand_position);
        }
      return playing_card;
        
    }

      //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump) override {

      assert(!hand.empty());
      std::vector<Card> non_led_hand;
      std::vector<Card> led_hand;

      Card lowest = hand[0];
      Card highest = hand[0];
      Card playing_card = hand[0];
      int highest_hand_position = 0;
      int lowest_hand_position = 0;



      //Seperates deck into trump, led, and non-trump cards
      for (int i = 0; i < hand.size(); i++) {
        if(hand[i].get_suit() == led_card.get_suit())
          led_hand.push_back(hand[i]);
        else
          non_led_hand.push_back(hand[i]);
      }

      //If all cards are non-led hands, play the lowest card
      if(non_led_hand.size() == MAX_HAND_SIZE) {
        for (int i = 0; i < MAX_HAND_SIZE; i++) {
          if (Card_less(hand[i], lowest, trump)) {
              lowest = hand[i];
              lowest_hand_position = i;
          }
        }
        playing_card = hand[lowest_hand_position];
        hand.erase(hand.begin() + lowest_hand_position);
      }

      //If there is at least one non led card, play the highest card in hand
      else {
        for (int i = 0; i < led_hand.size(); i++) {
        highest = led_hand[0];
        if (!Card_less(led_hand[i], highest, trump)) {
            highest = hand[i];
            highest_hand_position = i;
        }
        }
        playing_card = hand[highest_hand_position];
        hand.erase(hand.begin() + highest_hand_position);
        }
      return playing_card;
    
}

};

// ==========================================
// HumanPlayer Implementation
// ==========================================
class HumanPlayer : public Player {
private:
    std::string name;
    std::vector<Card> hand;

  void print_hand() const {
  for (size_t i=0; i < hand.size(); ++i)
    std::cout << "Human player " << name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
    }

public:
  HumanPlayer(const std::string &name_in) : name(name_in) {}

    //EFFECTS returns player's name
    const std::string & get_name() const override {
        return name;
    }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, 
                          bool is_dealer,
                          int round, 
                          Suit &order_up_suit) 
                          const override {
        // TODO: Implement Human player make_trump strategy (prompt 
        //user via std::cin/std::cout)
        std::string status;

        print_hand();

        if (round == 1) {
        std::cout << "Human player " << 
        name << ", please enter a suit, or \"pass\":\n";
        std::cin >> status;

        if (status == "pass")  {
          return false;
        }

        if (status != "pass") {
          //order_up_suit = string_to_suit(status);
          return true;
        }
        else {
          return false;
        }
      }
      else {
        std::cout << "Human player " << 
        name << ", please enter a suit, or \"pass\":\n";
        std::cin >> status;

        if (status == "pass")  {
          return false;
        }

        if (status != "pass") {
          //order_up_suit = string_to_suit(status);
          return true;
        }
        else {
          return false;
        }
      }

        // else if (status == "Spades") {
        //   order_up_suit == SPADES;
        //   return true;
        // }

        // else if (status == "Hearts") {
        //   order_up_suit == HEARTS;
        //   return true;
        // }

        // else if (status == "Clubs") {
        //   order_up_suit == CLUBS;
        //   return true;
        // }

        // else if (status == "Diamonds") {
        //   order_up_suit == DIAMONDS;
        //   return true;
        // }
        // return false;
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override {
      assert(!hand.empty());
      print_hand();
      int discard = 0;
      int discard_upcard = -1;
      std::cout << "Discard upcard: [-1]\n";
      std::cout << "Human player " << name << ", please select a card to discard:\n";
      std::cin >> discard;

      if (discard != discard_upcard) {
        hand.erase(hand.begin() + discard);
        hand.push_back(upcard);
        std::sort(hand.begin(), hand.end());
    }
    }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
    Card lead_card(Suit trump) override {
        assert(!hand.empty());
        print_hand();

        Card led = hand[0];
        int card_num = 0;
        std::cout << "Human player " << name << ", please select a card:\n";      
        std::cin >> card_num;
        led = hand[card_num];

        hand.erase(hand.begin() + card_num);
        std::sort(hand.begin(), hand.end());

        return led;
    }

    //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump) override {
        assert(!hand.empty());
        print_hand();

        Card led = hand[0];
        int card_num = 0;
        std::cout << "Human player " << name << ", please select a card:\n";      
        std::cin >> card_num;
        led = hand[card_num];

        hand.erase(hand.begin() + card_num);
        std::sort(hand.begin(), hand.end());

        return led;
    }
};


// ==========================================
// Factory Function & Operators
// ==========================================

Player * Player_factory(const std::string &name, 
  const std::string &strategy) {
    if (strategy == "Simple") {
        return new SimplePlayer(name);
    }
    if (strategy == "Human") {
        return new HumanPlayer(name);
    }
    
    // Invalid strategy if we get here
    assert(false);
    return nullptr;
}

 std::ostream & operator<<(std::ostream &os, const Player &p) {
   os << p.get_name();
    return os;
  }
