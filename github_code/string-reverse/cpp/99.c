/*************************************************************************************************
 ** Program Filename:	main.cpp
 ** Author:				Stephanie Holcomb
 ** Date:				October 18, 2015
 ** Description:		main implementation file for Lab 4 - Recursion
 ** Input:				None
 ** Output:				console only
 ***************************************************************************************************/
 

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string> 
#include <sstream>
#include <vector>
 
const int SIZE = 200;

int numTriangle(int);
int sumNums(int arraySum[], int size);
void getNums(std::string);
std::string stringReverse(std::string);
int arraySum[SIZE];



int main() {
 
 
       int choose;
       int numRows;
       int value;
       std::string strInput;
       std::string strValue;
 
 
 
       do {
              choose = 0;
              std::cout << "\n\nChoose one: " << std::endl;
              std::cout << "1) Reverse a String" << std::endl;
              std::cout << "2) Calculate the sum of an array" << std::endl;
              std::cout << "3) Calculate a triangular number" << std::endl;
              std::cout << "4) Quit" << std::endl;
 
              std::cin >> choose;
 
              switch (choose) {
 
              case 1:  
                     std::cout << "\nPlease enter a string" << std::endl;
					 std::cin.ignore(1000, '\n');
                     std::getline(std::cin,strInput);
					 std::cout << "\n" << std::endl;
					 // call stringReverse (recursion) function
                     strValue = stringReverse(strInput);
                     std::cout << "\nThe reverse of " << strInput << " is: " << strValue << "\n";
                     break;
					 
              case 2:
 
                     std::cout << "\nPlease enter a string of up to 200 numbers, each separated by a space" << std::endl;
                     std::cin.ignore(1000, '\n');
                     std::getline(std::cin,strInput);
					 // call getNums function to get integers from string
                     getNums(strInput);
					 //call sumNums (recursion) function to sum array values
                     value = sumNums(arraySum, SIZE);
					 
                     std::cout << "\nThe sum of your numbers is: " << value ;
					break;
					
              case 3:
			  
                     std::cout << "\nPlease enter the number of rows of pins" << std::endl;
                     std::cin >> numRows;
					 // call numTriangle to calculate number of pins
                     value = numTriangle(numRows);
                     std::cout << "\n" << numRows << " rows equals " << value << " pins." << std::endl;
                     break;
					 
              case 4:
					 // Quit message
                     std::cout << "\nThank you for playing!" << std::endl;
                     return 0;
                     break;
					 
              default:
			  
                     std::cout << "Please try again" << std::endl;
                     break;
              }
 
       } while ((choose != 'X') && (choose != 'x'));
 
 
}


/*************************************************************************************************
 ** Function:			numTriangle
 ** Description:		The function is called by main and gets user input for  # rows and returns 
 **						  triangular number
 ** Parameters:			numRows
 ** Pre-Conditions:		None
 ** Post-Conditions:	None
 ***************************************************************************************************/

int numTriangle(int numRows)
{
       if (numRows == 0) { // Base Case = 0
              return 0;
       }
       else {
              return (numRows + numTriangle(numRows - 1));
       }
}



/*************************************************************************************************
 ** Function:			stringReverse
 ** Description:		The function is called by main. Gets user input string, reverses it  
 **						  recursively, and prints it out.
 ** Parameters:			string variable
 ** Pre-Conditions:		None
 ** Post-Conditions:	None
 ***************************************************************************************************/

std::string stringReverse(std::string strInput) {
 
       if (strInput.length() == 0) { // Base Case = 0
              return "";
       }
       else {
			  
              std::string end(1,strInput[strInput.length() - 1]); // get last cahracter
			  std::cout << strInput[strInput.length()-1] << std::endl; //each character followed by line return
              std::string rest = stringReverse(strInput.substr(0, strInput.length() - 1));
              return end + rest;
       }
 
 
}

 
/*************************************************************************************************
 ** Function:			getNums
 ** Description:		The function is called by main. It uses stringstream to capture a string of  
 **						 integers from the user, split out and write to arraySum
 ** Parameters:			string variable
 ** Pre-Conditions:		None
 ** Post-Conditions:	None
 ***************************************************************************************************/
 
 void getNums(std::string strInput) {
 
       std::stringstream streamVector(strInput);

       int i = 0;
       while (streamVector >> arraySum[i])
       {
              i++;
       }
}
 

/*************************************************************************************************
 ** Function:			sumNums
 ** Description:		The function is called by main. It recursively sums the elements of arraySum  
 **						 starting with the first element.  
 ** Parameters:			string variable
 ** Pre-Conditions:		None
 ** Post-Conditions:	None
 ***************************************************************************************************/
 
int sumNums(int arraySum[], int size) {
       
       if (size == 0) { // Base case = 0
			return 0;
       }
       else {
			return arraySum[0] + sumNums((arraySum +1),size-1);
 
       }
 
}
 
