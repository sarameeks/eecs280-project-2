#include <iostream>
#include <vector>
#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include "Player.hpp"
#include "Card.hpp"
#include "Pack.hpp"

//make euchre.exe
// ./euchre.exe pack.in noshuffle 1 Adi Simple Barbara Simple Chi-Chih Simple Dabbala Simple

class Game {
 public:
//CONSTS
    std::vector<Player *> players;

    const int MAX_PLAYERS = 4;
    const int MAX_CARDS = 5;

    // Declare num FIRST so it exists before pts_win tries to use it
    std::string num;
    int pts_win = 1;

    //Often changing
    Card upturn;
    Suit trump;

    int team_ordered_trump = 0;

    int points = 0;
    int dealer = 0;
    int leader = 0;

    //Player 0, player 2
    int team_1_pts = 0;

    //Player 1, player 3
    int team_2_pts = 0;

    int round = 0;

    // Constructor to safely initialize things like pts_win from num


  //Players, points to win
  Game(int argc, char **argv, std::ifstream& pack_in_file) {

    //PACK INIT
    Pack pack(pack_in_file);
    
    //Shuffle?
    std::string shuffle_status = argv[2];
    if (shuffle_status == "shuffle")
      pack.shuffle();
    
    //Points to win
    num = argv[3];
    
    //Player init from arguments 4 -> 12
    for (int i = 4; i < 12; i += 2) {

      std::string player_name = argv[i]; 
      std::string player_type = argv[i + 1];
      players.push_back(Player_factory(player_name, player_type));

    }
    
  }

  void play() {
      
    int hand = 0;

    while (team_1_pts != pts_win || team_2_pts != pts_win) {
      std::cout << "Hand " << hand << "\n";
      deal();
      make_trump();
      play_hand();
      print_points();
      hand++;
    }

    if(team_1_pts > team_2_pts)
      std::cout << players[0]->get_name() << " and " << players[2]->get_name() << " win!" << std::endl;
    else
      std::cout << players[1]->get_name() << " and " << players[3]->get_name() << " win!" << std::endl;

    // for(int i = 0; i < players.size(); i++) {
    //   delete players[i];
  }

  void print_points() {
    std::cout << players[0]->get_name() << " and " << players[2] << " have " << team_1_pts << std::endl;
    std::cout << players[1]->get_name() << " and " << players[3] << " have " << team_2_pts << std::endl;
  }

  void play_hand() {

    Card winning_card;
    int player_took_trick = 0;
    int trick_takes_team_1 = 0;
    int trick_takes_team_2 = 0;
    int current_player = 0;

    for (int trick_num = 0; trick_num < 5; trick_num++) {

    if (leader >= MAX_PLAYERS) {
      leader = 0;
    }

      Card led_card = players[leader]->lead_card(trump);
      Suit led_card_suit = led_card.get_suit();
      Rank led_card_rank = led_card.get_rank();
      
    std::cout << led_card_rank << " of " << led_card_suit << " led by " << players[leader]->get_name() << std::endl;

    winning_card = led_card;
    player_took_trick = leader;

    //remaining players go

    std::vector<Card> played_cards(MAX_PLAYERS);
    //Play cards and find max card
    for (int i = 1; i < MAX_PLAYERS; i++) {

      current_player = (leader + i) % MAX_PLAYERS;
      played_cards[current_player] = (players[current_player]->play_card(led_card, trump));
      std::cout << played_cards[current_player].get_rank() << " of " <<  played_cards[current_player].get_suit() << " played by " << players[current_player]->get_name() << "\n";


    if (Card_less(winning_card, played_cards[current_player], led_card, trump)) {
        winning_card = played_cards[current_player];
        player_took_trick = current_player;
    }

  }

    if (player_took_trick == 0 || player_took_trick == 2) 
        trick_takes_team_1++;
      else if (player_took_trick == 1 || player_took_trick == 3) 
        trick_takes_team_2++;
        
      std::cout << players[player_took_trick]->get_name() << " takes the trick \n" << std::endl;

      leader = player_took_trick;

      dealer++;


  }

  //If the team that ordered up the trump suit takes 3 or 4 tricks, they get 1 point.
  //If the team that ordered up the trump suit takes all 5 tricks, they get 2 points. This is called a march.


  //team 1 evaluation if team 1 ordered trump
  if (team_ordered_trump == 1) {
    if(trick_takes_team_1 == 3 || trick_takes_team_1 == 4) {
      team_1_pts += 1;
      std::cout << players[0] << " and " << players[2] << " win the hand\n ";
    }
    else if(trick_takes_team_1 == 5) {
      team_1_pts += 2;
      std::cout << "march!\n"; 
      std::cout << players[0] << " and " << players[2] << " win the hand\n ";
    }
    else if(trick_takes_team_2 >= 3) {
      team_2_pts += 2;
      std::cout << "euchred!\n"; 
      std::cout << players[1] << " and " << players[3] << " win the hand\n ";
  }
  }

//team 2 evaluation if team 2 ordered trump
  else if (team_ordered_trump == 2) {
    if(trick_takes_team_2 == 3 || trick_takes_team_2 == 4) {
      team_2_pts += 1;
      std::cout << players[1] << " and " << players[3] << " win the hand\n ";
    }
    else if(trick_takes_team_2 == 5) {
      team_2_pts += 2;
      std::cout << "march!\n"; 
      std::cout << players[1] << " and " << players[3] << " win the hand\n ";
    }
    else if(trick_takes_team_1 >= 3) {
      team_1_pts += 2;
      std::cout << "euchred!\n"; 
      std::cout << players[0] << " and " << players[2] << " win the hand\n ";
  }
  }
  }

/*Directions:
In each hand, one player is designated as the dealer 
//(if humans were playing the game, the one who passes out the cards). 
In our game, player 0 deals during the first hand. Each subsequent hand, 
//the role of dealer moves one player to the left.

Each player receives five cards, dealt in alternating batches of 3 and 2. 
That is, deal 3-2-3-2 cards then 2-3-2-3 cards, for a total of 5 cards each. 
The player to the left of the dealer receives the first batch, and dealing 
continues to the left until 8 batches have been dealt.

Four cards remain in the deck after the deal. The next card in the pack is called the upcard (it is turned face up, 
//while the other cards are all face down). It plays a special role in the next phase. The three remaining cards are not used for the current hand.

//bach one: loop through four players in order starting at p1
//int i = batch1[k]

//Num of cards added
    

//for (int card_given_index = 0; card_given_index < batch1[player_index]; card_given_index++)
    //add_card();
*/
private:

  Pack pack;  

 void deal() {

  if (dealer >= MAX_PLAYERS)
    dealer = 0;

  int batch_1[8] = {3, 2, 3, 2, 2, 3, 2, 3};
  int batch_2[8] = {2, 3, 2, 3, 3, 2, 3, 2};
  //std::vector<Card> temp_card;

//if dealer is player 2 or player 0
//    if (dealer == 2 || dealer == 0) {
//  for (int player_index = 0; player_index < MAX_PLAYERS; player_index++) {
//    for (int card_given_index = 0; card_given_index <= batch_1[player_index]; card_given_index++) {
//        players[player_index]->add_card(pack.deal_one());
//  }
//  }
// }

  //for (int player_index = 0; player_index < MAX_PLAYERS; player_index++)
//  int player_index = 0;
//  for (int card_batch_index = 0; card_batch_index < 8; card_batch_index++) {
//    for (int card_index = 0; card_index < batch_1[card_batch_index]; card_index++) {
//      if (player_index == 3) {
//          player_index = 0;
//          players[player_index]->add_card(pack.deal_one());
//      }
//      else {
//          players[player_index]->add_card(pack.deal_one());
//          player_index++;
//      }  
//  }
// }

if (dealer == 2 || dealer == 0) {
  int player_index = (dealer + 1) % MAX_PLAYERS;
  for (int card_batch_index = 0; card_batch_index < 8; card_batch_index++) {
    for (int card_index = 0; card_index < batch_1[card_batch_index]; card_index++) {
      players[player_index]->add_card(pack.deal_one());
    }
    //if this is 4 then it breaks?????
      if (player_index == 3) 
          player_index = 0;
      else
        player_index++;

 }

  // else
  // for (int player_index = 0; player_index < MAX_PLAYERS; player_index++) {
  // for (int card_given_index = 0; card_given_index <= batch_2[player_index]; card_given_index++) {
  //      players[player_index]->add_card(pack.deal_one());
  // }
  // }

  std::cout << players[dealer]->get_name() << " deals\n";

    dealer++;

    upturn = pack.deal_one();

}

else if (dealer == 1 || dealer == 3) {
  int player_index = (dealer + 1) % MAX_PLAYERS;
  for (int card_batch_index = 0; card_batch_index < 8; card_batch_index++) {
    for (int card_index = 0; card_index < batch_2[card_batch_index]; card_index++) {
      players[player_index]->add_card(pack.deal_one());
    }
    //if this is 4 then it breaks?????
      if (player_index == 3) 
          player_index = 0;
      else
        player_index++;
  

  std::cout << players[dealer]->get_name() << " deals\n";

    dealer++;

    upturn = pack.deal_one();

  }
  }
}

  void make_trump() {
    //round 1 //////////////////////////////////////////////////////////////////////////////////////////
    std::cout << upturn.get_rank() << " of " << upturn.get_suit() << " turned up\n";
    
    bool ordered_up;

    round = 1;

    //To the left of the dealer!!!!!!!!!
    int player_index = (dealer + 1) % MAX_PLAYERS;

    //Go through 4 players
    for (int i = 0; i < 4; i++) {

      Suit upcard_suit = upturn.get_suit();

      //Go to each player
      ordered_up = players[player_index]->make_trump(upturn, (player_index == dealer), round, upcard_suit);

      //if a player decides to order up
      if(ordered_up == true) {
          //upcard_suit is changed by the "make_trump" function
          trump = upcard_suit;

          std::cout << players[player_index]->get_name() << " orders up " << trump << "\n" << "\n";
          
          //Take note of team that ordered up trump
            if(player_index == 2 || player_index == 0) {
              team_ordered_trump = 1;
            
            }
            else if(player_index == 1 || player_index == 3) {
            team_ordered_trump = 2;
            
            }
            return;
          //Exit the for loop, and the function
      }
      
      //If a player does not want to order up
      else {
          std::cout << players[player_index]->get_name() << " passes\n";
           if (player_index == 3) {
              player_index = 0;
            }
          else {
              player_index++;
            }
      }
      //The end of round 1
  }

//Round 2////////////////////////////////////////////////////////////////////////////////////////
    if (ordered_up == false) {

      round = 2;

//To the left of the dealer!!!!!!!!!
    player_index = (dealer + 1) % MAX_PLAYERS;

    //Go through 4 players
    for (int i = 0; i < 4; i++) {

      Suit upcard_suit = upturn.get_suit();

      //Go to each player
      ordered_up = players[player_index]->make_trump(upturn, (player_index == dealer), round, upcard_suit);

      //if a player decides to order up
      if(ordered_up == true) {
          //upcard_suit is changed by the "make_trump" function
          trump = upcard_suit;

          std::cout << players[player_index]->get_name() << " orders up " << trump << "\n" << "\n";
          
          //Take note of team that ordered up trump
            if(player_index == 2 || player_index == 0) {
              team_ordered_trump = 1;
            break;
            }
            else if(player_index == 1 || player_index == 3) {
            team_ordered_trump = 2;
            break;
          }
          //Exit the for loop, and the function
      }
      
      //If a player does not want to order up
      else {
          std::cout << players[player_index]->get_name() << " passes\n";
           if (player_index == 3) {
              player_index = 0;
            }
          else {
              player_index++;
            }
      }
    }
    }
  }

};



  //   round = 2;

  //   player_index = (dealer + 1) % MAX_PLAYERS;

  //   for (int i = 0; i < 4; i++) {

  //     Suit upcard_suit = upturn.get_suit();
  //     ordered_up = players[player_index]->make_trump(upturn, (player_index == dealer), round, upcard_suit);

  //     if(ordered_up == true) {
  //       trump = upcard_suit;
  //       std::cout << players[player_index]->get_name() << " orders up " << trump << "\n" << "\n";

  //         if(player_index == 2 || player_index == 0) {
  //           team_ordered_trump = 1;
  //         break;
  //         }

  //         else if(player_index == 1 || player_index == 3) {
  //           team_ordered_trump = 2;
  //         break;
  //         }
  //       }

  //     else {
  //           std::cout << players[player_index]->get_name() << " passes\n";
  //            if (player_index == 3) {
  //           player_index = 0;
  //           }
  //           else {
  //           player_index++;
  //           }
  //     }
  // }


  //   }
  //Implement screw the dealer?


int main(int argc, char **argv) {

//Command line arguments and file input check

    if (argc != 12) {
        std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
              << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
              << "NAME4 TYPE4\n";
        return 1;
    }

    std::string pack_in_file = argv[1];
    std::ifstream in(pack_in_file);
//Error check
    if (!in.is_open()) {
      std::cout << "Error opening" << pack_in_file << "\n";
        return 1; // Exit with failure status
    }


    Game game(argc, argv, in);
    game.play();

    //pack_file.close();

    return 0;
}

