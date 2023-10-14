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
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(test_image_width){
  Image *img = new Image;
  Image_init(img, 3, 4);

  int expected = 3;
  int actual = Image_width(img);

  ASSERT_EQUAL(expected, actual);

  delete img;
}

TEST(test_image_height){
  Image *img = new Image;
  Image_init(img, 3, 4);

  int expected = 4;
  int actual = Image_height(img);

  ASSERT_EQUAL(expected, actual);

  delete img;
}

TEST(test_image_set_pixel){
  Image *img = new Image;
  Image *test = new Image;
  Image_init(test, 5, 5);
  Image_init(img, 5, 5);
  
  Pixel p;
  p.r = 230;
  p.g = 0;
  p.b = 100;
  Image_fill(img, p);
  Image_fill(test, p);
  
  Pixel expected;
  expected.r = 5;
  expected.g = 0;
  expected.b = 250;
  Image_set_pixel(test, 1, 2, expected);
  Image_set_pixel(img, 1, 2, expected);

  ASSERT_TRUE(Image_equal(img, test));

  delete img;
  delete test;
}

TEST(test_image_get_pixel){
  Image *img = new Image;
  Image_init(img, 6, 7);
  Pixel expected;
  expected.r = 10;
  expected.g = 50;
  expected.b = 200;
  Image_set_pixel(img, 3, 4, expected);
  Pixel actual = Image_get_pixel(img, 3, 4);

  ASSERT_TRUE(Pixel_equal(expected, actual));
  delete img;
}

TEST(test_image_fill){
  Image *img = new Image;
  Image_init(img, 5, 6);
  Pixel fill;
  fill.r = 50;
  fill.g = 34;
  fill.b = 200;
  Image_fill(img, fill);
  bool truth = true;

  for (int r = 0; r < Image_height(img); ++r){
    for (int c = 0; c < Image_width(img); ++c){
      Pixel p = Image_get_pixel(img, r, c);
      if (p.r != fill.r || p.g != fill.g || p.b != fill.b){
        truth = false;
      }
    }
  }

  ASSERT_TRUE(truth);
  delete img;
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
