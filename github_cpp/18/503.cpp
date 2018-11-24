#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

void swap( char &a, char &b){
    char aux = a;
    a = b;
    b = aux;
}

char * reverseString(char* s){
    int nValidChars = 0;
    int i=0;
    while ( s[i] != '\0'){
        nValidChars++;
        i++;
    }
    for(int i=0; i <nValidChars/2; i++){
        swap(s[i], s[nValidChars-i-1]);
    }
    return s;
}

int main(){
    char s[9]  = "Testando";
    cout << reverseString(s) << endl;
    return 0;
}
