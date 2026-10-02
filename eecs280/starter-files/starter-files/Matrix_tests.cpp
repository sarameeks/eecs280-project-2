#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

//Does my function even work?
TEST(catch_matrix_column_of_min_value_in_row) {
  Matrix mat;
  const int width = 2;
  const int height = 2;
  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, 255);
  *Matrix_at(&mat, 1, 1) = 1;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(
    &mat, 1, 0, width), 1);
}
//Does my function return the leftmost min value?
TEST(catch_matrix_column_of_min_value_in_row2) {
  Matrix mat;
  const int width = 2;
  const int height = 2;
  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, 255);
  *Matrix_at(&mat, 0, 1) = 1;
  *Matrix_at(&mat, 0, 2) = 1;

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(
    &mat, 0, 0, width), 1);
}


TEST_MAIN() // Do NOT put a semicolon here
