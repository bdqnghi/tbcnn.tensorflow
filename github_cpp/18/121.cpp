# include <string>
# include <iostream>

using namespace std;

class ReverseString
{
    public:
    string reverseString(string c)
    {
        string reversed = c;

        int length = c.length();
        int mid = length/2;

        for (int i = 0; i< mid;i++)
        {
            char temp = reversed[i];

            reversed[i] = reversed[length-i-1];

            reversed[length-i-1] = temp;
        }
        return reversed;
    }

};

int main(void)
{
    ReverseString rs;

    string str("I am happy");

    cout<< rs.reverseString(str);

    return 0;
}
