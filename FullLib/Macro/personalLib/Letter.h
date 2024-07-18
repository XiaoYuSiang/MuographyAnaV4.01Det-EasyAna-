#include <iostream>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <algorithm>
using namespace std;


void FloToStr(double d, int befordigit=3, int Afterdigit=3){
  int Totaldigit=befordigit+Afterdigit;
  cout<< setw(Totaldigit) << setfill(' ') << fixed << setprecision(Afterdigit-1) << d;
}