#include <iostream>
#include <string>

using namespace std;

/*int editDistance (string x, string y)
{
    if (x == "")
        return y.length(); // base case
    else if (y == "")
        return x.length(); // base case
    else
    {
        int addDistance = editDistance(x, y.substr(0,y.length()-1)) + 1;
        int removeDistance = editDistance(x.substr(0,x.length()-1), y) + 1;
        int changeDistance = editDistance(x.substr(0,x.length()-1),
                                          y.substr(0,y.length()-1))
                             + (x[x.length()-1] == y[y.length()-1]) ? 0 : 1;
        return min(min(addDistance, removeDistance), changeDistance);
    }
}*/

int editDistance(string x, string y){
    if (x == "")
        return y.length(); // base case
    else if (y == "")
        return x.length(); // base case
    else
    {
        int addDistance = editDistance(x, y.substr(1)) + 1;
        int removeDistance = editDistance(x.substr(1), y) + 1;
        int changeDistance = editDistance(x.substr(1), y.substr(1))+ (x[0] == y[0]) ? 0 : 1;
        return min(min(addDistance, removeDistance), changeDistance);
    }
}
int main() {
    int min=0;
    int min2=0;
    string str1="ISLANDER";
    string srt2="SLANDER";

    //min = editDistance("ISLANDER", "SLANDER");
    //cout << "Edit distance" << min << endl;

    //min2 = editDistance("MART", "KARMA");
    //cout << "Edit distance" << min2 << endl;

    min = editDistance("Zei", "tri");
    cout << "Edit distance" << min << endl;

    return 0;
}