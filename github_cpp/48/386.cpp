//PALIN - The Next Palindrome
#include <bits/stdc++.h>
using namespace std;

string getNextPalindrome(string value){
    string nextP;
    nextP.assign(value);
    int size = value.size();
    int half_size = (int)round(size / 2.0);
    for (int i = 0, j=size-1; i < half_size;i++,j--){
        if (value[i] != value[j]){
            nextP[j]=value[i];
        }
    }
    int isNextPBigger = 0;
    for (int i = half_size - 1; i < size;i++){
        if (nextP[i] > value[i]){
            isNextPBigger = 1;
            break;
        } else if (nextP[i] < value[i]){
            break;
        } 
    }
    
    if (!isNextPBigger){
        int itLeft = half_size - 1;
        int itRight = half_size;
        int isNine = 1;
        if (size % 2 == 1){
            if (nextP[itLeft]=='9'){
                nextP[itLeft]='0';
                itLeft--;
            }else{
                isNine=0;
                nextP[itLeft]+=1;
            }
        }
        while(isNine){
            if (nextP[itLeft]=='9'){
                nextP[itLeft--]='0';
                nextP[itRight++]='0';
            }else {
                nextP[itLeft]+=1;
                nextP[itRight]+=1;
                isNine=0;
            }
        }
        
    }
    return nextP;
}

int main() {
    ios::sync_with_stdio(0); //input and output become more efficient.
    cin.tie();
    int num_inputs;
    cin >> num_inputs;
    
    while (num_inputs-- > 0){
        string value;
        cin >> value;
        int edgeCase = 1;
        for (char c: value){
            if (c != '9'){
                edgeCase = 0;
                break;
            }
        }
        if (edgeCase){
            value = string(value.size()+1,'0');
            value[0]='1';
        }
        cout << getNextPalindrome(value) << "\n";
    }
}