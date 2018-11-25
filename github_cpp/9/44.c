/*
 * =====================================================================================
 *
 *       Filename:  exercise_7-31.cpp
 *
 *     Description: 7.31 (Print a String Backward)
 *								  
 *
 *        Version:  1.0
 *        Created:  29/05/18 09:05:00
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Şükrü Görkem Okur - gorkemokur@gmail.com
 *  	 Organization:  -
 *
 *   Begin at the beginning, … and go on till you come to the end: then stop.
 *   —Lewis Carroll
 * =====================================================================================
 */

#include<iostream>
#include<string>
using namespace std;

void stringReverse(string str,int b){
	if(str[b] == '\0'){return;}
	stringReverse(str,b+1);
	cout<<str[b];
}

int main(){
    string str{"Hello"};
    stringReverse(str,0);

return 0;
}
