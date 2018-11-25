






#include <iostream>
#include <string>
using namespace std;










void Reverse(string original, string& lanigiro);





void Reverse(string original, string& lanigiro) {

    
    lanigiro.clear();

    
    int len = (int)original.length();
    for (int i = len - 1; i >= 0; --i) {

        lanigiro.push_back( original.at(i) );

    }

}




string Reverse(string original) {

    char temp;
    int len = (int)original.length();

    
    for (int i = 0; i < (len / 2); ++i) {

        temp = original[i];
        original[i]           = original[len - 1 - i];
        original[len - 1 - i] = temp;

    }

    return original;
}






int main() {

    string original, lanigiro;

    cout << "----------------------------------------" << endl;
    cout << "Text 1" << endl;
    cout << "----------------------------------------" << endl;

    cout << "\n==Reversing the stfing (Using void function)==\n" << endl;

    
    cout << "Enter a string: ";
    cin >> original;
    cout << "==> ";

    
    Reverse(original, lanigiro);
    cout << lanigiro << endl;
    cout << endl;

    cout << "Clearing original and lanigiro variables..." << endl;
    original.clear();
    lanigiro.clear();
    cout << endl;

    cout << "----------------------------------------" << endl;
    cout << "Text 2" << endl;
    cout << "----------------------------------------" << endl;

    cout << "\n==Reversing the stfing (Using void function)==\n" << endl;

    
    cout << "Enter a string: ";
    cin >> original;
    cout << "==> ";

    
    lanigiro = Reverse(original);

    
    cout << lanigiro << endl;

    return 0;
}

