#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int min_dist(string word1, string word2) {
    std::vector<std::vector<int>> arr;
    arr.resize(word1.size());
    for (auto& item : arr)
    {
        item.resize(word2.size());
    }


    if (word1[0] == word2[0])
    {
        arr[0][0] = 0;            
    }
    else
    {
        arr[0][0] = 1;
    }

    for (int i = 1; i < word1.size(); i++)
    {
        if (word1[i] == word2[0])
            arr[i][0] = arr[i-1][0];
        else
            arr[i][0] = arr[i-1][0] + 1;
    }

    for (int j = 1; j < word2.size(); j++)
    {
        if (word1[0] == word2[j])
            arr[0][j] = arr[0][j-1];
        else
            arr[0][j] = arr[0][j-1] + 1;            
    }

    for (int i = 1; i < word1.size(); i++)
    {
        for (int j = 1; j < word2.size(); j++)
        {
            if (word1[i] == word2[j])
            {
                arr[i][j] = arr[i-1][j-1];
            }
            else
            {
                arr[i][j] = std::min(arr[i-1][j-1], std::min(arr[i-1][j], arr[i][j-1])) + 1;
            }
        }
    }

    return arr[word1.size()-1][word2.size()-1];
}

int main(int argc, char**)
{
    cout << min_dist("a", "c") << endl;
    cout << min_dist("a", "a") << endl;
    cout << min_dist("a", "ab") << endl;
    cout << min_dist("ac", "ab") << endl;
    cout << min_dist("ab", "ab") << endl;
    cout << min_dist("abc", "abd") << endl;
    cout << min_dist("abz", "abgh") << endl;
    return 0;
}

