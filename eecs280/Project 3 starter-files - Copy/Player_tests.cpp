#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here
/*
Simple Player make_trump() Bug #2 - 
Your tests fail to catch a bug in this function.
Simple Player make_trump() Bug #2 - 
Your test cases should verify that a 
player will accurately make decisions based 
on the number of trump cards they have, 
including any relevant special cases.
*/


TEST_MAIN()
