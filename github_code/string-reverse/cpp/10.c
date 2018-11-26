#include<iostream>
#include<string>

std::string reverse( std::string word ) {
	

	for(int i = 0; i < word.size(); ++i ) {
                std::cout << word[i] << " ";
        }
	std::cout << "-------------------------------" << std::endl;

	char a='a';
	char b='b';
	char *front=&a;
	char *back=&b;
	for (int i=0;i< (word.size()/2);i++) {
		front[0]=word[i];
		back[0]=word[word.size()-1-i];
		word[i]=*back;
		word[word.size() - i - 1 ] = *front;
	}


return word;
}
int  main() {

	
	std::string word = "Hello World";
	
	std::string result = reverse( word );
	std::cout << result << std::endl;	


return 0;
}
