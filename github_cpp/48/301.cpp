#include <iostream>
#include <cmath>

using namespace std;

bool isnum(int num);

int main()
{
    int num;

    cout << "Enter a sequance of numbers to test "
          << "if its a palindrome " << endl;
    cin >> num;
    if (isnum(num) == true )
    cout << num << " is a palindrome ";

    else
    cout << num << " is not a palindrome " << endl;

    return 0;
}

bool isnum(int num)
{
    int pwr = 0;

    if (num < 10)
    {
        return true;
    }
    else
    {
        while (num / static_cast<int>(pow(10.0,pwr)) >= 10 )
        pwr++;
        while ( num >= 10 )
        {
        int tenpwr = static_cast<int>(pow(10.0, pwr));

        if ((num / tenpwr) != ( num % 10))
          return false;
        else
        {
          num = num % tenpwr;
          num = num / 10;
          pwr = pwr - 2;
        }
    }
     return true;
    }
}
