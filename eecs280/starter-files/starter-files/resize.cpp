#include <iostream>
#include<fstream>
#include<sstream>
#include "Image.hpp"
#include "Matrix.hpp"


using namespace std;

int get_file() {
}

int main(int argc[], char *argv[]) {

  string input_file_name = argv[1];
  string output_file_name = argv[2];
  int desired_width = argc[3];
  int desired_height = argc[4];
//if (5 comd line argument)
  if (*argc < 4) {
    //////////////////////////////////////
  }

  ifstream file_in(input_file_name);

  if (!file_in.is_open()) {
        cout << "Error: Could not open the file!" << std::endl;
        return 1;
    }

  ofstream file_out(argv[2]);

  Image image_in;

  Image_init(&image_in, file_in);



  //If no height argument is supplied, the original height is kept 
  //(i.e. only the width is resized).

}

// * [ ] **1. Set up args & error check**
// * Check if `argc` is 4 or 5.
// * Extract filenames and target width/height (`stoi`).


// * [ ] **2. Read input file**
// * Open `ifstream`. If it fails, print error and `return 1`.
// * Read the image with `Image_init` and close the stream.


// * [ ] **3. Validate width & height**
// * Make sure desired width/height are $> 0$ and $\le$ original size.
// * If invalid, print Usage error and `return 1`.


// * [ ] **4. Run seam carving**
// * Call `seam_carve(&img, desired_width, desired_height)`.


// * [ ] **5. Save output file**
// * Open `ofstream`. If it fails, print error and `return 1`.
// * Write with `Image_print`, close the stream, and `return 0`.