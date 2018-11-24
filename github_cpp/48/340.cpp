#include <iostream>
#include <string>
//using terador = std::string::iterator;
bool palindrome(std::string str_) {
	if(str_.size() == 1) {
		return true;
	}
	else if(str_.size() == 2) {
		if(str_[0] == str_[1]) {
			return true;
		}
		else
			return false;
	}
	str_.pop_back();
	std::string temp;
	temp.assign(str_, 1, std::string::npos);
	return palindrome(temp);
}

int main() {
	std::string str = "noon";
	std::cout << std::distance(str.begin(), str.end()) << "\n";

	if(palindrome(str)) {
		std::cout << "The string '" << str << "' IS a palindrome.\n"; 
	}
	else
		std::cout << "'"<< str << "' IS NOT a palindrome.\n";

	return 0;
}