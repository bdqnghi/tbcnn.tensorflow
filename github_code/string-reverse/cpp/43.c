/* Total Time Complexity = O(n)
	Extra memory for stack as we are pushing all characters to stack.
	Extra space will be proportional to number of characters.
	So space complexity = O(n) */

#include <iostream>
#include <stack>
using namespace std;

void string_reverse(char *c, int n)
{

	stack<char> s;

	/* Time complexity is O(n) */
	for(int i = 0; i < n; i++)
	{
		s.push(c[i]); /* Pushing characters to stack */
	}

	/* Time complexity is O(n) */
	for(int i = 0; i < n; i++)
	{
		c[i] = s.top();  /* adding top character to string */
		s.pop();  		 /* Popping character form stack */
	}

}

int main()
{
	char c[100];
	cout<<"Enter a string: ";
	cin>>c;
	//gets(c);
	string_reverse(c, strlen(c));
	cout<<c<<endl;
	//puts(c);
	//printf("%s", c);
}