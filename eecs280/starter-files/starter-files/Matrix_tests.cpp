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
// //Does my function return the leftmost min value?
// TEST(catch_matrix_column_of_min_value_in_row2) {
//   Matrix mat;
//   const int width = 2;
//   const int height = 2;
//   Matrix_init(&mat, width, height);
//   Matrix_fill(&mat, 255);
//   //Put the min value at column 1 and 2
//   *Matrix_at(&mat, 0, 1) = 1;
//   *Matrix_at(&mat, 0, 2) = 1;
// }

// //Tests for inclusive row start
//   TEST(Matrix_column_of_min_value_in_row3) {
//     Matrix mat;
//     const int width = 3;
//     const int height = 1;

//     Matrix_init(&mat, width, height);
//     Matrix_fill(&mat, 255);

//     *Matrix_at(&mat, 0, 0) = 1;  
//     *Matrix_at(&mat, 0, 2) = 1;  

//     ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 2, 3), 2);
// }

//From spec: The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//Tests for exclusive row end
TEST(Matrix_column_of_min_value_in_row_test1) {
    Matrix mat;
    const int width = 4;
    const int height = 1;

    Matrix_init(&mat, width, height);
    Matrix_fill(&mat, 255);


    *Matrix_at(&mat, 0, 2) = 2;  

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 2, width), 2);
}

//Does column start and column end work?
TEST(Matrix_column_of_min_value_in_row_test2) {
    Matrix mat;
    const int width = 4;
    const int height = 1;

    Matrix_init(&mat, width, height);
    Matrix_fill(&mat, 255);


    *Matrix_at(&mat, 0, 2) = 2;  

    //the minimum in the row is 1 but 
    //the minimum in the tange we want is 2
    *Matrix_at(&mat, 0, 0) = 1;  

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 2, width), 2);
}

//Does the function use the leftmost column? Or does it incorrectly use the 
//rightmose minimum value?
TEST(Matrix_column_of_min_value_in_row_test) {
    Matrix mat;
    const int width = 5;
    const int height = 1;

    Matrix_init(&mat, width, height);
    Matrix_fill(&mat, 255);


    *Matrix_at(&mat, 0, 3) = 1;  

    *Matrix_at(&mat, 0, 1) = 1;  

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, width), 1);
}

//Test matrix max
TEST(Matrix_max_test) {
    Matrix mat;
    const int width = 2;
    const int height = 2;

    Matrix_init(&mat, width, height);
    Matrix_fill(&mat, 1);


    *Matrix_at(&mat, 0, 1) = 255;    

    ASSERT_EQUAL(Matrix_max(&mat), 255);
}

//Test matrix at
TEST(Matrix_at_test) {
    Matrix mat;
    const int width = 2;
    const int height = 2;

    Matrix_init(&mat, width, height);
    Matrix_fill(&mat, 0);
  //int *Matrix_at(Matrix *mat, int row, int column)
    *Matrix_at(&mat, 0, 1) = 1;
    
    //int Matrix_column_of_min_value_in_row
    //(const Matrix *mat, int row, int column_start, int column_end)
    Matrix_column_of_min_value_in_row(&mat, 0, 0, width);
  
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, width), 0);
}


TEST_MAIN() // Do NOT put a semicolon here

