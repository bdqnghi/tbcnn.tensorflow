// File: binary-search.cpp
// Inclass exercise for 1/22/2017

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib> // exit()

// Function prototypes go here
void read_datafile (std::ifstream &infile, // REC'D/P'BACK: input filestream
		    int array[],           // P'BACK: array to be filled
		    int &num_elements);    // P'BACK: # elements filled
void print_array (const int array[],       // REC'D: array to print
		  int num_elements);       // REC'D: # elements filled

// Function: binary_search
// Returns the index of the target in an array
int binary_search (const int an_array[],   // RECV'D: array to search
		   int target,             // RECV'D: target value
		   int first,              // REDV'D: lower bound of range to search
		   int last);               // REDV'D: upper bound of range to search
		   
const int ARRAY_SIZE = 100;  // C++ constant; don't use #define

int main(int argc, char *argv[])
{
   using namespace std;

   if (argc != 2)
   {
      cerr << "Usage: " << argv[0] << " datafile" << endl;
      exit(1);
   }

   ifstream infile (argv[1]);
   if (!infile)
   {
      cerr << "Unable to open file: " << argv[1] << endl;
      exit(1);
   }

   int n, target, position;
   int an_array[ARRAY_SIZE];

   read_datafile(infile, an_array, n);
   print_array(an_array, n);

   cout << "\nEnter an integer to search for: ";
   cin >> target;

   // Function call goes here
   position = binary_search(an_array, target, 0, n-1);
   if (position != -1)
      cout << "The target is at index: " << position << endl;
   else
      cout << "The target is not in the file" << endl;

   return 0;
}
int binary_search (const int an_array[],   // RECV'D: array to search
		   int target,             // RECV'D: target value
		   int first,              // REDV'D: lower bound of range to search
		   int last)               // REDV'D: upper bound of range to search
{
  // Base cases:
  //      - finding target
  //      - not finding the target

  // check if indexes have crossed
  if (last < first)
    return -1;  // not found, -1 is not a valid array index

  // compute the index of the midpoint value
  int mid_index = (first + last)/2;
  // check if it is the target
  if (an_array[mid_index] == target)
    return mid_index; //return the index of the target

  if (target < an_array[mid_index])
    //search the "left" half
    //smaller-caller cuts the search space in half
    return binary_search(an_array, target, first, mid_index-1);

  //otherwise search the "right" half
  return binary_search(an_array, target, mid_index+1, last);

}

// Function definitions goes here
void read_datafile (std::ifstream &infile, int array[], int &num_elements)
{
   int value;
   num_elements = 0;
   while (infile >> value)  // read until end of file
   {
      array[num_elements] = value;
      num_elements++;
   }
} // end read_datafile

void print_array (const int array[], int num_elements)
{
   using namespace std;

   for (int i = 0; i < num_elements; i++)
   {
      if (i % 10 == 0)
	 cout << endl;
      cout << setw(4) << array[i];
   }
   cout << endl;
} // end print_array
