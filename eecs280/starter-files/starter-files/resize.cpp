#include <iostream>
#include<fstream>
#include<sstream>
#include "Image.hpp"
#include "Matrix.hpp"
#include "processing.hpp"


using namespace std;

int main(int argc, char *argv[]) {
  
  if (argc < 4 || argc > 5) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  string input_file_name = argv[1];
  string output_file_name = argv[2];
  int desired_width = atoi(argv[3]);
  int desired_height = 0;


  //Bring in file
  ifstream file_in(input_file_name);
  Image image_in;

  if (!file_in.is_open()) {
        cout << "Error opening file: " << input_file_name << endl;
        return 1;
    }

    
  //Begin process of changing file
  Image_init(&image_in, file_in);
  
  if (argc == 5) {
    desired_height = atoi(argv[4]); }
  else if (argc == 4) {
    desired_height = Image_height(&image_in);
  }

    if (desired_width < 0 || 
      desired_width > Image_width(&image_in) || 
      desired_height > Image_height(&image_in) || 
      desired_height < 0) {

    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return 1;
  }
  
  ofstream file_out(output_file_name);

  if (!file_in.is_open() || !file_out.is_open()) {
        cout << "Error opening file: " << input_file_name << endl;
        return 1;
    }

  seam_carve(&image_in, desired_width, desired_height);
  Image_print(&image_in, file_out);

  file_in.close();
  file_out.close();

  return 0;

}