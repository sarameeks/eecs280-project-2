#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here


TEST(test_card_ctor2) {
    Card c(TWO, DIAMONDS);
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(DIAMONDS, c.get_suit());
}


TEST(test_card_ctor3) {
    Card c(JACK, DIAMONDS);
    ASSERT_EQUAL(JACK, c.get_rank());
    ASSERT_EQUAL(DIAMONDS, c.get_suit());
}


TEST(test_card_ctor4) {
    Card c(QUEEN, HEARTS);
    ASSERT_EQUAL(QUEEN, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(input_test) {

    std::istringstream input("Two of Spades");
    Card card;
    input >> card;
  

  ASSERT_EQUAL(card.get_rank(), TWO);
  ASSERT_EQUAL(card.get_suit(), SPADES);

}

TEST(jack_test) {

    std::istringstream input("Jack of Spades");

    Card card;
    input >> card;
  

  ASSERT_EQUAL(card.get_rank(), JACK);
  ASSERT_EQUAL(card.get_suit(), SPADES);

}

TEST(face_test) {

    std::istringstream input("Jack of Spades");

    Card card;
    input >> card;
  

  ASSERT_EQUAL(card.is_face_or_ace(), true);

}

TEST(face_test2) {

    std::istringstream input("Two of Spades");

    Card card;
    input >> card;
  

  ASSERT_EQUAL(card.is_face_or_ace(), false);

}


TEST(face_test3) {

    std::istringstream input("Ace of Spades");

    Card card;
    input >> card;
  

  ASSERT_EQUAL(card.is_face_or_ace(), true);

}

TEST(compare) {
    
    std::istringstream input1("Ace of Spades");

    Card card1;
    input1 >> card1;

    std::istringstream input2("Ace of Spades");

    Card card2;
    input2 >> card2;

    std::istringstream input3("Queen of Hearts");

    Card card3;
    input3 >> card3;

    std::istringstream input4("Queen of Diamonds");

    Card card4;
    input4 >> card4;
  
    ASSERT_EQUAL(card1 == card2, true);
    ASSERT_EQUAL(card2 == card1, true);
    ASSERT_EQUAL(card3 == card1, false);
    ASSERT_EQUAL(card1 == card3, false);


    ASSERT_EQUAL(card2 != card2, false);
    ASSERT_EQUAL(card2 != card3, true);
    ASSERT_EQUAL(card2 < card3, false);
    ASSERT_EQUAL(card2 > card3, true);
    ASSERT_EQUAL(card2 >= card3, true);

    // ASSERT_EQUAL(card2 <= card3, false);
    ASSERT_EQUAL(card3 == card4, true);


}

TEST (bower1) {
    std::istringstream input1("Jack of Diamonds");

    Card card1;
    input1 >> card1;

    ASSERT_EQUAL(card1.is_trump(HEARTS), true);
     

    std::istringstream input2("Jack of Diamonds");

    Card card2;
    input2 >> card2;

    ASSERT_EQUAL(card2.is_trump(SPADES), false);

}

//operator==(const Card &lhs, const Card &rhs), tests fail to catch a bug

TEST_MAIN()
