#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

//Whether image indeed fills 
TEST(test_image_init1) {
  Image img;
  Image_init(&img, 1, 1);

  Image test;
  Image_init(&test, 1, 1);
  Pixel zeros = {0, 0 ,0};
  Image_fill(&test, zeros);

  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n1 1\n255\n";
  correct << "0 0 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());

}

//Are both images initialized the same between both image_init?
TEST(image_init_test2) {

    std::string sample_img = 
        "P3\n"
        "1 1\n"
        "255\n"
        "255 255 255\n";

    std::istringstream input_img(sample_img);
    Image img;
    Image_init(&img, input_img);

    Image answer_img;
    Image_init(&answer_img, 1, 1);

    Pixel fill = {255, 255, 255};

    Image_set_pixel(&answer_img, 0, 0, fill);

    ASSERT_TRUE(Image_equal(&img, &answer_img));
}



//Are both images initialized the same between both image_init?
TEST (image_init_test3) {
  std::string sample_img = 
  "P3\n"
  "3 1\n"
  "255\n"
  "255 " "255 " "255 \n" 
  "255 " "255 " "255 \n"
  "255 " "255 " "255 \n";


  std::istringstream input_img(sample_img);
    Image img;
    Image_init(&img, input_img);

    Image answer_img;
    Image_init(&answer_img, 3, 1);

    Pixel fill = {255, 255, 255};

    Image_set_pixel(&answer_img, 0, 0, fill);
    Image_set_pixel(&answer_img, 0, 1, fill);
    Image_set_pixel(&answer_img, 0, 2, fill);

    assert(Image_equal(&img, &answer_img));
}

//Are both images initialized the same between both image_init?
TEST (image_init_test4) {
  std::string sample_img = 
  "P3\n"
  "3 1\n"
  "255\n"
  "255 " "255 " "255 \n" 
  "255 " "255 " "255 \n"
  "255 " "255 " "255 \n";


  std::istringstream input_img(sample_img);
    Image img;
    Image_init(&img, input_img);

    Image answer_img;
    Image_init(&answer_img, 3, 1);

    Pixel fill = {255, 255, 255};

    Image_set_pixel(&answer_img, 0, 0, fill);
    Image_set_pixel(&answer_img, 0, 1, fill);
    Image_set_pixel(&answer_img, 0, 2, fill);

    ASSERT_EQUAL(Image_width(&img), Image_width(&answer_img));
}

//Are both images initialized the same between both image_init?
TEST (image_init_test5) {
  std::string sample_img = 
  "P3\n"
  "3 1\n"
  "255\n"
  "255 " "255 " "255 \n" 
  "255 " "255 " "255 \n"
  "255 " "255 " "255 \n";


  std::istringstream input_img(sample_img);
    Image img;
    Image_init(&img, input_img);

    Image answer_img;
    Image_init(&answer_img, 3, 1);

    Pixel fill = {255, 255, 255};

    Image_set_pixel(&answer_img, 0, 0, fill);
    Image_set_pixel(&answer_img, 0, 1, fill);
    Image_set_pixel(&answer_img, 0, 2, fill);

    ASSERT_EQUAL(Image_height(&img), Image_height(&answer_img));
}

TEST (image_fill_test) {
  std::string sample_img = 
  "P3\n"
  "3 1\n"
  "255\n"
  "255 " "255 " "255 \n" 
  "255 " "255 " "255 \n"
  "255 " "255 " "255 \n";


  std::istringstream input_img(sample_img);
    Image answer_img;
    Image_init(&answer_img, input_img);



    Image img;
    Image_init(&img, 3, 1);
    Pixel fill = {255, 255, 255};
    Image_fill(&img, fill);

    assert(Image_equal(&img, &answer_img));
}

TEST_MAIN() // Do NOT put a semicolon here
