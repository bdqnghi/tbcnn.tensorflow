#include <vector>
#include <iostream>
#include <iomanip>


using std::vector;

using namespace std;
template <typename T>
bool palindrome(const vector<T> &v)
{
	bool result = true;
	vector <T>::const_iterator asd = v.begin();
	vector <T>::const_reverse_iterator qwe = v.rbegin();
	while (asd != v.end())
	{
		if (*asd != *qwe)
		{
			result = false;
			break;
		}
		asd++;
		qwe++;
	}
	return result;
}
int main()
{
	vector<int> vP;
	int size;
	int input;
	cout << "\nchecking/analyzing palindromes using vectors.";
	cout << "\nenter size: ";
	cin >> size;
	cout << "enter vector:\n\n";
	for (int i = 0; i < size; i++)
	{
		cin >> input;
		vP.push_back(input);
	}
	if (palindrome(vP))
		cout << "\nit is a palindrome\n";
	else
		cout << "\nit is not a palindrome\n";

	system("pause");
	return 0;
}