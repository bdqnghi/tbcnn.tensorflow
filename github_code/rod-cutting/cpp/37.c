#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

struct myData{
    int profit;
    int numberOfCuts;
};

//bottom up approach
myData cutRodUp(int* price, int length)
{
    myData data;
    int cut[11] = {0,1,1,1,2,2,1,2,2,2,1};
    const int size = length + 1;
    int rod[size];
    data.numberOfCuts = cut[size];

    rod[0] = 0;
    for (int j = 1; j <= length; j++)
    {
        int q = -99999999;
        for (int i = 1; i <= j; i++)
        {
            q=max(q,price[i]+rod[j-i]);
        }
        rod[j]=q;
    }

    data.profit = rod[length];
    return data;
}

int main()
{
    int input = 0;
    myData profit;
    int price[11] = {0,1,5,8,9,10,17,17,20,24,30};

    while(input != -1)
    {
        cout << "enter -1 to exit" << endl << "Enter in a length of rod to find the maximun profit: ";
        cin >> input;
        if (input != -1)
        {
            profit = cutRodUp(price,input);
            //profit = cutRodDown(price,input);
        }
        cout << "profit: " << profit.profit << endl;
        cout << "number of cuts: " << profit.numberOfCuts << endl;
    }
    

    return 0;
}