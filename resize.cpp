#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include "processing.hpp"
using namespace std;

int main(int argc, char * argv[]) {
  if (argc < 4 || argc > 5) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n" << endl;
    return 1;
  }  

  ifstream inFile;
  inFile.open(argv[1]);
  if (!inFile.is_open()){
    cout << "Error opening file: " << argv[1] << endl;
    return 1;
  }

  ofstream outFile;
  Image * input = new Image;
  Image_init(input, inFile);

  inFile.close();

  string width = argv[3];
  int w = stoi(width);
  if (w <= 0 || w > Image_width(input)){
    cout << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  int h = Image_height(input);
  if (argc == 5){
    string height = argv[4];
    h = stoi(height);
    if (h <= 0 || h > input->height){
    cout << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
    }
  }

  seam_carve(input, w, h);
  outFile.open(argv[2]);
  ostringstream os;
  if (outFile.is_open()){
    Image_print(input, os);
    outFile << os.str();
  }
  outFile.close();
  delete input;
}