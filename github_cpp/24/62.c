


#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib> 


void read_datafile (std::ifstream &infile, 
		    int array[],           
		    int &num_elements);    
void print_array (const int array[],       
		  int num_elements);       



int binary_search (const int an_array[],   
		   int target,             
		   int first,              
		   int last);               
		   
const int ARRAY_SIZE = 100;  

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

   
   position = binary_search(an_array, target, 0, n-1);
   if (position != -1)
      cout << "The target is at index: " << position << endl;
   else
      cout << "The target is not in the file" << endl;

   return 0;
}
int binary_search (const int an_array[],   
		   int target,             
		   int first,              
		   int last)               
{
  
  
  

  
  if (last < first)
    return -1;  

  
  int mid_index = (first + last)/2;
  
  if (an_array[mid_index] == target)
    return mid_index; 

  if (target < an_array[mid_index])
    
    
    return binary_search(an_array, target, first, mid_index-1);

  
  return binary_search(an_array, target, mid_index+1, last);

}


void read_datafile (std::ifstream &infile, int array[], int &num_elements)
{
   int value;
   num_elements = 0;
   while (infile >> value)  
   {
      array[num_elements] = value;
      num_elements++;
   }
} 

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
} 
