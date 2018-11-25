

#include<iostream>
#include<vector>
#include<array>
#include<cstdlib>
#include "lab06.h"

using std::vector;
using std::array;
using std::string;
using std::cout;
using std::endl;


template<typename T, size_t n>
void print(T &x, string name);


template<typename T>
bool lessThan(T x, T y);


template<typename T>
bool greaterThan(T x, T y);


template<typename T>
bool doNothing(T x, T y);


void test1();


void test2();


void test3();


void test4();


void test5();


void test6();


int main(){
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  return EXIT_SUCCESS;
}

template<typename T, size_t n>
void print(T &x, string name){
  int size = (int) n;
  cout << name << " = [";
  for(int i = 0; i < size - 1; i++){
    cout << x[i] << ", ";
  }
  cout << x[size - 1] << ']' << endl;
}

template<typename T>
bool lessThan(T x, T y){
  if(x < y){ return true; }
  else { return false; }
}

template<typename T>
bool greaterThan(T x, T y){
  if(x > y){ return true; }
  else { return false; }
}

template<typename T>
bool doNothing(T x, T y){
  return false;
}

void test1(){
  cout << "test1" << endl;
  vector<int> x = {-9, 28, 1, 17, 0, 17, 17, 28};
  array<int, 8> y = {-9, 28, 1, 17, 0, 17, 17, 28};
  int z [8] = {-9, 28, 1, 17, 0, 17, 17, 28};
  print<vector<int>, 8>(x, "x");
  print<array<int, 8>, 8>(y, "y");
  print<int[8], 8>(z, "z");
  bubbleSort(x, greaterThan);
  bubbleSort(y, greaterThan);
  bool (* great)(int, int) = &greaterThan<int>;
  bubbleSort(z, great);
  print<vector<int>, 8>(x, "x");
  print<array<int, 8>, 8>(y, "y");
  print<int[8], 8>(z, "z");     
}

void test2(){
  cout << "test2" << endl;
  vector<char> x = {'z', 'b', 'A', 'p', 'a', 'a', 'q', '0', 'o', 'O', '2'};
  array<char, 11> y = {'z', 'b', 'A', 'p', 'a', 'a', 'q', '0', 'o', 'O', '2'};
  char z [11] = {'z', 'b', 'A', 'p', 'a', 'a', 'q', '0', 'o', 'O', '2'};
  bool (* g)(char, char) = &greaterThan<char>;
  bubbleSort(x, g);
  bubbleSort(y, g);
  bubbleSort(z, g);
  print<vector<char>, 11>(x, "x");
  print<array<char, 11>, 11>(y, "y");
  print<char[11], 11>(z, "z");
  bool (* lt)(char, char) = &lessThan<char>; 
  bubbleSort(x, lt);
  bubbleSort(y, lt);
  bubbleSort(z, lt);
  print<vector<char>, 11>(x, "x");
  print<array<char, 11>, 11>(y, "y");
  print<char[11], 11>(z, "z"); 
}

void test3(){
  cout << "test3" << endl;
  vector<string> x = {"Zoey", "Worf", "Data", "Picard", "Janeway", "Sisco", "Spock"};
  array<string, 7> y = {"Zoey", "Worf", "Data", "Picard", "Janeway", "Sisco", "Spock"};
  string z [7] = {"Zoey", "Worf", "Data", "Picard", "Janeway", "Sisco", "Spock"};
  bool (* noSwap)(string, string) = &doNothing<string>;
  bubbleSort(z, noSwap);
  print<string[7], 7>(z, "z");
  bool (* gt)(string, string) = &greaterThan<string>;
  bubbleSort(x, gt);
  bubbleSort(y, gt);
  bubbleSort(z, gt);
  print<vector<string>, 7>(x, "x");
  print<array<string, 7>, 7>(y, "y");
  print<string[7], 7>(z, "z");     
}

void test4() {
  cout << "test4" << endl;
  vector<double> x = {-1.43231551, 1.3e7, 0.43215, -0.57316889, 2.64321, 7.1e8, -1.533, 0.0032134};
  array<double, 8> y = {-1.43231551, 1.3e7, 0.43215, -0.57316889, 2.64321, 7.1e8, -1.533, 0.0032134};
  double z [8] = {-1.43231551, 1.3e7, 0.43215, -0.57316889, 2.64321, 7.1e8, -1.533, 0.0032134};
  bool (* noSwap)(double, double) = &doNothing<double>;
  bubbleSort(x, noSwap);
  bubbleSort(y, noSwap);
  bubbleSort(z, noSwap);
  print<vector<double>, 8>(x, "x");
  print<array<double, 8>, 8>(y, "y");
  print<double[8], 8>(z, "z");
  bubbleSort(x, greaterThan);
  print<vector<double>, 8>(x, "x");
  bubbleSort(y, greaterThan);
  bubbleSort(z, greaterThan);
  print<array<double, 8>, 8>(y, "y");
  print<double[8], 8>(z, "z");
  bool (* less)(double, double) = &lessThan<double>;
  bubbleSort(x, less);
  bubbleSort(y, less);
  bubbleSort(z, less);
  print<vector<double>, 8>(x, "x");
  print<array<double, 8>, 8>(y, "y");
  print<double[8], 8>(z, "z");
}

void test5(){
  cout << "test5" << endl;
  vector<float> x = {3.14159, 8.2e6, -94321, 11.4315, 9.2, 89.2241, -0.000041, 2.542685432};
  array<float, 8> y = {3.14159, 8.2e6, -94321, 11.4315, 9.2, 89.2241, -0.000041, 2.542685432};
  float z [8] = {3.14159, 8.2e6, -94321, 11.4315, 9.2, 89.2241, -0.000041, 2.542685432};
  bool (* ns)(float, float) = &doNothing<float>;
  bubbleSort(x, ns);
  bubbleSort(y, ns);
  bubbleSort(z, ns);
  print<vector<float>, 8>(x, "x");
  print<array<float, 8>, 8>(y, "y");
  print<float[8], 8>(z, "z");
  bubbleSort(x, greaterThan);
  print<vector<float>, 8>(x, "x");
  bubbleSort(y, greaterThan);
  bubbleSort(z, greaterThan);
  print<array<float, 8>, 8>(y, "y");
  print<float[8], 8>(z, "z");
  bool (* leT)(float, float) = &lessThan<float>;
  bubbleSort(x, leT);
  bubbleSort(y, leT);
  bubbleSort(z, leT);
  print<vector<float>, 8>(x, "x");
  print<array<float, 8>, 8>(y, "y");
  print<float[8], 8>(z, "z");
}

void test6(){
  cout << "test6" << endl;
  vector<long> x = {43214, 53247895, 1919383, 52, 50193, -24321, -11335, 118538};
  array<long, 8> y = {43214, 53247895, 1919383, 52, 50193, -24321, -11335, 118538};
  long z [8] = {43214, 53247895, 1919383, 52, 50193, -24321, -11335, 118538};
  bool (* noSw)(long, long) = &doNothing<long>;
  bubbleSort(x, noSw);
  bubbleSort(y, noSw);
  bubbleSort(z, noSw);
  print<vector<long>, 8>(x, "x");
  print<array<long, 8>, 8>(y, "y");
  print<long[8], 8>(z, "z");
  bubbleSort(x, greaterThan);
  print<vector<long>, 8>(x, "x");
  bubbleSort(y, greaterThan);
  bubbleSort(z, greaterThan);
  print<array<long, 8>, 8>(y, "y");
  print<long[8], 8>(z, "z");
  bool (* le)(long, long) = &lessThan<long>;
  bubbleSort(x, le);
  bubbleSort(y, le);
  bubbleSort(z, le);
  print<vector<long>, 8>(x, "x");
  print<array<long, 8>, 8>(y, "y");
  print<long[8], 8>(z, "z");
}
