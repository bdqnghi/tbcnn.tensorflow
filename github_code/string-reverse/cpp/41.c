/*
 * Program: Program to reverse words and characters in a string
 * 
 * Author: Jwala Mohith Girisha
 * 
 */
 
#include<iostream>
#include<string.h>

using namespace std;

void reverse_words(char string[], char reverse_string[]);
void string_cat(char revstr[], int revlen, char addstr[], int len);

void reverse_chars(char string[], char reverse_string[]);

void reverse_words_chars(char string[], char reverse_string[]);

int main(){
	
	char string[] = "Hi Mohith ! How are you doing today ?";
	char reverse_string[1001] = "";
	
	int sel;
	
	cout << "What would you like to do?\n1. Reverse words\n2. Reverse words and chars\n3. Reverse chars in words\nEnter your choice: ";
	cin >> sel;
	
	cout << "\nString to be reversed\n" << string << endl;
	
	//cin.getline(string,1000);
	
	switch(sel){
		
		case 1:
				reverse_words(string, reverse_string);
				break;
		case 2: 
				reverse_chars(string, reverse_string);
				break;
		case 3:
				reverse_words_chars(string, reverse_string);
				break;
		default:
				cout << "Invalid choice\n";
				break;
			}
			
	cout << "Reversed string\n";
	cout << reverse_string;

	
	return 0;
}


void reverse_words(char string[], char reverse_string[]){
	
	int i = 0;
	int j = 0;
	
	while(1){
		
		char temp[20];

		while(*(string+i) != ' ' && *(string+i) != '\0'){
			*(temp+j) = *(string+i);
			j++; i++;
		}
		*(temp+j) = ' ';
		
		//strcat(reverse_string,temp);
		string_cat(reverse_string, i, temp, j+1);

		if(*(string+i) =='\0')
			break;
		i++; 
		j =  0;
		memset( temp, 0, sizeof(temp) );
		}
	
	
}

void string_cat(char revstr[], int revlen, char addstr[], int len){
	
	
	for(int i=revlen-1; i >=0; i--){
		
		*(revstr+i+len) = *(revstr+i);
		
	}
	
	for(int j=0; j<len; j++){
		
		*(revstr+j) = *(addstr+j);
		
	}
	
}
	
void reverse_chars(char string[], char reverse_string[]){
	
	
	int i = 0;
	
	while(*(string+i) != '\0'){
				
			char temp[1];
			
			temp[0] = *(string+i);
			
			string_cat(reverse_string, i, temp, 1);
			
			i++;
			
		}
	
	
}


void reverse_words_chars(char string[], char reverse_string[]){

	int i = 0;
	int j = 0;
	
	while(1){
		
		char temp[20]; char temprev[20];

		while(*(string+i) != ' ' && *(string+i) != '\0'){
			*(temp+j) = *(string+i);
			j++; i++;
		}
		*(temp+j) = ' ';
		
		//strcat(reverse_string,temp);
		
		reverse_chars(temp, temprev);
		strcat(reverse_string, temprev);
		//string_cat(reverse_string, i, temprev, j+1);

		if(*(string+i) =='\0')
			break;
		i++; 
		j =  0;
		memset( temp, 0, sizeof(temp) );
		memset( temprev, 0, sizeof(temprev) );
		}
	
}


