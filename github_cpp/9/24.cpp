/*================================================================
 *   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
 *
 *   FileName   ：Insertion-Sort.cpp
 *   Author     ：He Hongyu (Ray)
 *   Date       ：2018-02-19
 *   Description：
 *   Email		: hongyu.he@hotmail.com
 *	 GitHub		: https://github.com/HongyuHe
 ================================================================*/
#include <iostream>
#include <vector>

using namespace std;

int main ()
{
    int total = 0;
    int num;

    vector<int> sequence;
    sequence.clear();

    cin >> total;
    cout << "Input: " << endl;
    for (int i = 0; i < total; i++)
    {
        cin >> num;
        sequence.push_back(num);
    }
    cout << "End: " << *(sequence.end() - 1) << endl;
    cout << "Size: " << (int)sequence.size() << endl;
    cout << "\n";

    for (int j = 1; j < total; j++)
    {
        int key = sequence[j];

        int i = j - 1;
        while (i >= 0 && sequence[i] > key)
        {
            sequence[i + 1] = sequence[i];
            i--;
        }
        sequence[i + 1] = key;

        //Print：
        for (vector<int>::iterator it = sequence.begin(); it != sequence.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }

    cout << "Output: ";

    for (vector<int>::iterator it = sequence.begin(); it != sequence.end(); it++)
    {
        cout << *it << " ";
    }

    return 0;

}
