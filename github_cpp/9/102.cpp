
#include "stringReverse.hpp"
#include <iostream>
#include <string>


void enterString()
{
    std::string userIn;
    std::cout << "Please enter a string you'd like to have reversed: " << std::endl << std::endl;
    std::getline(std::cin, userIn);
    std::cout << std::endl;
    std::cout << "   Reverses to  --->   ";
    stringReverse(userIn);
    std::cout << std::endl << std::endl;
    startMenu();
}


void stringReverse(std::string stringIn)
{
    if (stringIn.length()==0)
        return;
    else
    {
        std::cout << stringIn[stringIn.length()-1];
        
        
        std::string newString=stringIn.substr(0, stringIn.length()-1);
        stringReverse(newString);
    }
}
