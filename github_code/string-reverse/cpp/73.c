#include<iostream>
#include<cstring>
#include<string.h>
#include<ctype.h>
using namespace std;

int countSpace(string s){
int cs=0;
for(int i=0;i<s.size();i++){
    if(s[i]==' '){
        cs++;
    }
}
return cs;
}

string printReverse(string s){
int len=s.size(),j=0,prev;
string s1="";
int space=0;
//If Len =0
if(len==0){
    return s;
}
else{
    s1.resize(len);
    space=countSpace(s);
    //if space is zero EX:CODINGISFUN
    if(space==0){
        return s;
    }
    else{
        for(int i=len-1;i>=0;i--){
            if(s[i]==' '){
                --space;
                if(j==0){
                    for(int k=i+1;k<len;k++){
                        s1[j++]=s[k];
                    }
                    s1[j++]=' ';
                    prev=i;
                }
                else{
                    for(int k=i+1;k<prev;k++){
                        s1[j++]=s[k];
                    }
                    s1[j++]=' ';
                    prev=i;
                }
            }
            if(space==0){
                for(int k=0;k<prev;k++){
                    s1[j++]=s[k];
                }
                break;
            }
        }
        return s1;
        }
    }

}


int main(){
//I am Mohit Coding is Fun
string input;
getline(cin,input);
string outpt=printReverse(input);
cout<<outpt<<endl;
return 0;
}
