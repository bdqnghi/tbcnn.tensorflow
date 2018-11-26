/*************************************************************************************************************************
 * 424
 * 
 *
 * Classification:
 *
 * Author:
 *   Javier Gonzalez Nova <javigonzalez@udec.cl>
 *
 * Description:
 *
 *
 */

#include <iostream>
#include <string.h>
#include <stdio.h>
#define MAX 110
using namespace std;

void stringReverse(char[]);
void longAdd(char[],char[]);

int main(){
    char num[MAX],res[MAX];
    memset(res,'\0',MAX);
    while(cin.getline(num, MAX)){
        stringReverse(num);
        longAdd(res, num);
        memset(num, '\0', MAX);
    }
    stringReverse(res);
    printf("%s\n", res);
    return 0;
}
void longAdd(char res[],char num[])
{
    int i,a,b,c=0;
    for(i = 0; res[i] || num[i]; i++){
        a = res[i]?res[i]-48:0; /*Si res[i] != '\0', a es igual al digito, si no a es 0.*/
        b = num[i]?num[i]-48:0;
        res[i] = (a+b+c)%10+48;
        c = (a+b+c)/10;
    }
    /*Si quedo resto luego de sumar todos los numeros...*/
    if(c)
        res[i]=c+48;
}

void stringReverse(char str[]){
    int i, len=strlen(str), n=len/2;
    char ch;
    for(i = 0; i < n; i++){
        ch=str[i];
        str[i]=str[len-i-1];
        str[len-i-1]=ch;
    }
}
