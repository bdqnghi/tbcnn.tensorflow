#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <memory>

using namespace std;

unique_ptr<char> reverse(const char * const p)
{
	size_t nchars(strlen(p)), len(nchars+1);
	unique_ptr<char> result(new char[len]);
	reverse_copy(p,p+nchars,result.get());
	result.get()[len] = '\0';
	return result;
}

int main (int argc, const char* const argv[])
{
	char const *p = "seven";
	unique_ptr<char> p2 = reverse(p);

	auto f0 = [&p2](){ cout << p2 << endl; };

	f0();

	//same thing but in place. lambda just for giggles, should use std::swap()
	auto f1 = [&p2]() mutable { 
		char temp,  * const p = p2.get();
		size_t nchars = strlen(p), endpos(nchars-1);
		for (size_t i=0; i<(endpos)/2 ; ++i )
		{
			temp=p[i];
			p[i] = p[endpos-i];
			p[endpos-i] = temp;
		}
	};

	f1();
	f0();

	return 0;
}
