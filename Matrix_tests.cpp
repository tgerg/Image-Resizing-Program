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
TEST(test_fill_basic){
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST(test_matrix_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  *Matrix_at(mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(mat, actual);

  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST(test_matrix_width){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 4);

  int expected = 3;
  int actual = Matrix_width(mat);

  ASSERT_EQUAL(expected, actual);

  delete mat;
}

TEST(test_matrix_height){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 4);

  int expected = 4;
  int actual = Matrix_height(mat);

  ASSERT_EQUAL(expected, actual);

  delete mat;
}

TEST(test_matrix_row){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 6);

  int actual = Matrix_row(mat, Matrix_at(mat, 2, 3));
  int expected  = 2;

  ASSERT_EQUAL(expected, actual);

  delete mat;
}

TEST(test_matrix_column){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 6);

  int actual = Matrix_column(mat, Matrix_at(mat, 2, 3));
  int expected  = 3;

  ASSERT_EQUAL(expected, actual);

  delete mat;
}

TEST(test_matrix_at){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 2);
  *Matrix_at(mat, 0, 0) = 1;
  *Matrix_at(mat, 0, 1) = 2;
  *Matrix_at(mat, 1, 0) = 3;
  *Matrix_at(mat, 1, 1) = 4;
  int * index = Matrix_at(mat, 0, 0);
  ++index;
  int actual = *(Matrix_at(mat, 0, 1));
  int expected = 2;

  ASSERT_EQUAL(expected, actual);

  delete mat;
}

TEST(test_matrix_fill){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 2);
  *Matrix_at(mat, 0, 0) = 8;
  *Matrix_at(mat, 0, 1) = 8;
  *Matrix_at(mat, 1, 0) = 8;
  *Matrix_at(mat, 1, 1) = 8;

  Matrix *act = new Matrix;
  Matrix_init(act, 2, 2);
  
  Matrix_fill(act, 8);
  ASSERT_TRUE(Matrix_equal(mat, act));
  delete mat;
  delete act;
}

TEST(test_matrix_fill_border){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  Matrix *act = new Matrix;
  Matrix_init(act, 3, 3);
  
  *Matrix_at(act, 0, 0) = 2;
  *Matrix_at(act, 0, 1) = 2;
  *Matrix_at(act, 0, 2) = 2;
  *Matrix_at(act, 1, 0) = 2;
  *Matrix_at(act, 1, 1) = 0;
  *Matrix_at(act, 1, 2) = 2;
  *Matrix_at(act, 2, 0) = 2;
  *Matrix_at(act, 2, 1) = 2;
  *Matrix_at(act, 2, 2) = 2;

  Matrix_fill(mat, 0);
  Matrix_fill_border(mat,2);

  ASSERT_TRUE(Matrix_equal(mat,act));

  delete mat;
  delete act;
}

TEST(test_matrix_max){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 4);

  Matrix_fill(mat, 0);
  *Matrix_at(mat, 0, 2) = 3;
  *Matrix_at(mat, 3, 2) = 4;
  *Matrix_at(mat, 1, 2) = 8;
  *Matrix_at(mat, 0, 1) = -1;
  int expected = 8;

  ASSERT_EQUAL(Matrix_max(mat), expected);

  delete mat;
}

TEST(test_matrix_column_of_min_value_in_row_and_min_value){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 4);

  *Matrix_at(mat, 2, 0) = 2;
  *Matrix_at(mat, 2, 1) = -8;
  *Matrix_at(mat, 2, 2) = -50;
  *Matrix_at(mat, 2, 3) = -20;
  int expected_col = 2;
  int expected_min = -50;

  ASSERT_EQUAL(expected_col, Matrix_column_of_min_value_in_row(mat, 2, 1, 3));
  ASSERT_EQUAL(expected_min, Matrix_min_value_in_row(mat, 2, 1, 3));

  delete mat;
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
