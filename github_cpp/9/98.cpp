







#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

void reverseString(char word[], int length);    

int main(){
    
    char userString[4];
    
    int length = strlen(userString);    
    
    cout <<" Enter a word that has four letters " << "\n";
    
    cin >> userString;                  
    
    reverseString(userString, 4);       
    
    
    
    return 0;
}


void reverseString(char word[], int length)
{
    char *headP = &word[0];         
    char *tailP = &word[length-1];  
    char userString[4];
    
    cout << word << endl;           
    
    char temp;                      
    
    while(headP < tailP){           
        temp = *tailP;
        *tailP = *headP;
        *headP = temp;
        headP++;                    
        tailP--;	                
    }
    cout << word << endl;           
}

