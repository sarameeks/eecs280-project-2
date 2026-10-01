#include <cassert>
#include <vector>
#include "processing.hpp"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------






// ------------------------------------------------------------------
// You may change code below this line!


// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
    
  Matrix_init(energy, Image_width(img), Image_height(img));
  Matrix_fill(energy, 0);

  //Traverse entire image
 
  for (int r = 1; r < Image_height(img) - 1; r++) {     
    for (int c = 1; c < Image_width(img) - 1; c++) {    

      Pixel center = {0, 0, 0};
      Pixel north = {0, 0, 0};
      Pixel east = {0, 0, 0};
      Pixel south = {0, 0, 0};
      Pixel west = {0, 0, 0};

 
      center = Image_get_pixel(img, r, c);

      north = Image_get_pixel(img, r, c - 1);

      east  = Image_get_pixel(img, r + 1, c);

      south = Image_get_pixel(img, r, c + 1);

      west  = Image_get_pixel(img, r - 1, c);
    
      *Matrix_at(energy, r, c) = squared_difference(north, south) + squared_difference(west, east);

    }
  }

  Matrix_fill_border(energy, Matrix_max(energy));
  
}
  

  // assert(false); // TODO Replace with your implementation!
  // assert(squared_difference(Pixel(), Pixel())); // TODO delete me, this is here to make it compile




// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {

  Matrix_init(cost, Matrix_width(energy), Matrix_height(energy));

  //row = y;
  //column = x;

  //Fill in costs for the first row (index 0). 
  //The cost for these pixels is just the energy.
  int row = 0;
  for (int column = 0; column < Matrix_width(cost); column++ ) {
    *Matrix_at(cost, row, column) = *Matrix_at(energy, row, column);
  }

  for (int row = 1; row < Matrix_height(cost); row++) {     
    for (int column = 0; column < Matrix_width(cost); column++) {
      
      if (column == 0) {
        *Matrix_at(cost, row, column) = *Matrix_at(energy, row, column) 
        + Matrix_min_value_in_row(cost, row - 1, column, column + 2);
      }
      else if (column == Matrix_width(cost) - 1) {
        *Matrix_at(cost, row, column) = *Matrix_at(energy, row, column) 
        + Matrix_min_value_in_row(cost, row - 1, column -1, column + 1);
      }
      else {
        *Matrix_at(cost, row, column) = *Matrix_at(energy, row, column) 
        + Matrix_min_value_in_row(cost, row - 1, column -1, column + 2);
      }
    }
  }
}

// REQUIRES: cost points to a valid Matrix
// EFFECTS:  Returns the vertical seam with the minimal cost according to the given
//           cost matrix, represented as a vector filled with the column numbers for
//           each pixel along the seam, with index 0 representing the lowest numbered
//           row (top of image). The length of the returned vector is equal to
//           Matrix_height(cost).
//           While determining the seam, if any pixels tie for lowest cost, the
//           leftmost one (i.e. with the lowest column number) is used.
//           See the project spec for details on computing the minimal seam.
//           Note: When implementing the algorithm, compute the seam starting at the
//           bottom row and work your way up.
vector<int> find_minimal_vertical_seam(const Matrix* cost) {

  vector<int> seam_values;
//row = y;
//column = x;
  int size = 0;
  size = (Matrix_width(cost) * Matrix_height(cost));

  for (int i = 0; i < size && (seam_values.size() < Matrix_height(cost)); i++) {

    for (int y = 0; y < Matrix_height(cost); y++) {
      for (int x = 0; x < Matrix_width(cost); x++) {

        seam_values[i] = *Matrix_at(cost, y, (Matrix_column_of_min_value_in_row(cost, y, x, Matrix_width(cost))));
        
    }
  }
  }

  return seam_values;
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam.size() == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Declare a new variable to hold the smaller Image, and
//           then do an assignment at the end to copy it back into the
//           original image.

//////////////////////////FIX ME
void remove_vertical_seam(Image *img, const vector<int> &seam) {
  
  Image new_image;
  Image_init(&new_image, (Image_width(img) - 1), Image_height(img));

//row = y;
//column = x;

  int i = 0; 

  for (int y = 0; y < Image_height(&new_image); y++) {     
    for (int x = 0; x < Image_width(&new_image); x++) {
        i++

      if (seam[i] == x) {

        continue;
      }
      else  {    

      Image_set_pixel(&new_image, y, x, Image_get_pixel(img, y, x));

    }
  
}
  }

  img = &new_image;

}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
void seam_carve_width(Image *img, int newWidth) {
  
  Matrix energytemp;
  Matrix costtemp;
  vector<int> seamtemp;

  compute_energy_matrix(img, &energytemp);
  compute_vertical_cost_matrix(&energytemp, &costtemp);
  seamtemp = find_minimal_vertical_seam(&costtemp);

  if (Image_width(img) != newWidth) {

    remove_vertical_seam(img, seamtemp);

  }
  
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {

  rotate_right(img);
  seam_carve_width(img, newHeight);

}

// REQUIRES: img poiwnts to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {

  seam_carve_height(img, newHeight);
  seam_carve_width(img, newWidth);

}
