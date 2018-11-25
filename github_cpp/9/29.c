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





void reverseRecursive(char *str){
    if(*str != '\0'){ 
        reverseRecursive(str+1);
        cout << *str;
    }

}




void reverseIterative(char *str){
    int len = getLength(str);
    for(int i = 0; i < len/2; i++){
        
        swap(str[i],str[len-i-1]);

        
        
        
    }
}

char* reversePString(char*str){

    int len = getLength(str);
    char *reversed = (char*)malloc(sizeof(char) * len);
    reversed[len] = '\0';
    for(int i = len-1; i >= 0; i--){
        reversed[len-i-1] = str[i];
        
    }
    return reversed;
}





int getLength(char *str){
    int count = 0;
    while(*str){
        str++;
        count++;
    }
    return count;
}
