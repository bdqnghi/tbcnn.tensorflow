#include <iostream>

using namespace std;


void reverseIterative (char *str);
void reverseRecursive(char *str);
char* reversePString(char*str);
int getLength(char*str);


int main()
{

    char *pString = "Hello world!";
    char string[50] = "Hello World!";

    reverseRecursive(string); cout << endl;
    reverseIterative(string);

    cout << string << endl;
    cout << reversePString(pString) << endl;
    return 0;
}


//This does not change the char pointer at all just iterates
//to the end then prints from the end to the beginning

void reverseRecursive(char *str){
    if(*str != '\0'){ //can remove != '\0' like in getLength if desired.
        reverseRecursive(str+1);
        cout << *str;
    }

}

//This actually changes the value of the string. However, the char must
//be in an array not a pointer since the pointer would be read only and
//will crash. See below for pointer.
void reverseIterative(char *str){
    int len = getLength(str);
    for(int i = 0; i < len/2; i++){
        //can use swap or a temp variable
        swap(str[i],str[len-i-1]);

        //char temp = str[i];
        //str[i] = str[len-i-1];
        //str[len-i-1] = temp;
    }
}

char* reversePString(char*str){

    int len = getLength(str);
    char *reversed = (char*)malloc(sizeof(char) * len);
    reversed[len] = '\0';
    for(int i = len-1; i >= 0; i--){
        reversed[len-i-1] = str[i];
        //cout << reversed[i];
    }
    return reversed;
}


//***Helper function to avoid string library.

//Gets the length of a char pointer, must be null terminated.
int getLength(char *str){
    int count = 0;
    while(*str){
        str++;
        count++;
    }
    return count;
}
