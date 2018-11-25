
 

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
					 
                     strValue = stringReverse(strInput);
                     std::cout << "\nThe reverse of " << strInput << " is: " << strValue << "\n";
                     break;
					 
              case 2:
 
                     std::cout << "\nPlease enter a string of up to 200 numbers, each separated by a space" << std::endl;
                     std::cin.ignore(1000, '\n');
                     std::getline(std::cin,strInput);
					 
                     getNums(strInput);
					 
                     value = sumNums(arraySum, SIZE);
					 
                     std::cout << "\nThe sum of your numbers is: " << value ;
					break;
					
              case 3:
			  
                     std::cout << "\nPlease enter the number of rows of pins" << std::endl;
                     std::cin >> numRows;
					 
                     value = numTriangle(numRows);
                     std::cout << "\n" << numRows << " rows equals " << value << " pins." << std::endl;
                     break;
					 
              case 4:
					 
                     std::cout << "\nThank you for playing!" << std::endl;
                     return 0;
                     break;
					 
              default:
			  
                     std::cout << "Please try again" << std::endl;
                     break;
              }
 
       } while ((choose != 'X') && (choose != 'x'));
 
 
}




int numTriangle(int numRows)
{
       if (numRows == 0) { 
              return 0;
       }
       else {
              return (numRows + numTriangle(numRows - 1));
       }
}





std::string stringReverse(std::string strInput) {
 
       if (strInput.length() == 0) { 
              return "";
       }
       else {
			  
              std::string end(1,strInput[strInput.length() - 1]); 
			  std::cout << strInput[strInput.length()-1] << std::endl; 
              std::string rest = stringReverse(strInput.substr(0, strInput.length() - 1));
              return end + rest;
       }
 
 
}

 

 
 void getNums(std::string strInput) {
 
       std::stringstream streamVector(strInput);

       int i = 0;
       while (streamVector >> arraySum[i])
       {
              i++;
       }
}
 


 
int sumNums(int arraySum[], int size) {
       
       if (size == 0) { 
			return 0;
       }
       else {
			return arraySum[0] + sumNums((arraySum +1),size-1);
 
       }
 
}
 
