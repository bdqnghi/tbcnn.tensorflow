#include<iostream>
#include<cstring>
using namespace std;


void reverse_String(int start,int end,char input[]){

char temp;

while(start<=end){

    temp=input[end];
    input[end]=input[start];
    input[start]=temp;
    start++;
    end--;
 }
}
void reverseEachWord(char name[]){

int start=0,end=0;
int len=strlen(name);
for(int i=0;i<=len;i++){

    if(name[i]==' ' || name[i]=='\0'){
        reverse_String(start,end-1,name);
        start=end+1;
        end=start;
        }

    else{
        end++;
    }
 }
}
int main(){

char input[100]="Coding Ninjas";
reverseEachWord(input);
for(int i=0;i<strlen(input);i++)
    cout<<input[i];
}
