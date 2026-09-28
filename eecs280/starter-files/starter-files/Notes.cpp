


// //To create a Matrix, first declare a variable 
// and then use an initializer function.

// Matrix m; // create a Matrix object in local memory
// Matrix_init(&m, 100, 100); // initialize it as a 100x100 matrix




// //Once a Matrix is initialized, it is considered valid. Now we can use any of the functions declared in Matrix.hpp to operate on it.

// Matrix_fill(&m, 0); // fill with zeros

// // fill first row with ones
// for (int c = 0; c < Matrix_width(m); ++c) {
//   *Matrix_at(&m, 0, c) = 1; // see description below
// }

// Matrix_print(&m, cout); // print matrix to cout



// //CREATE VECTOR

// // create a vector with 100 elements, all initialized to the value 0
// std::vector<int> vec(100, 0);

// // modify an existing vector to have 200 elements with value 0
// vec.assign(200, 0);

// // replace an existing vector with a new one containing 50 elements,
// // all initialized to the value 0
// vec = std::vector<int>(50, 0);