

#include "EditDistance.h"
#include <vector>
#include <algorithm>

int EditDistance::minDistance(string word1, string word2)
{
    return getMinDistance2(word1, word2);
}

int EditDistance::getMinDistance(string& word1, string& word2, int index1, int index2)
{
    int length1 = word1.length();
    int length2 = word2.length();

    if (index1 == length1)
    {
        return length2 - index2;
    }
    else if (index2 == length2)
    {
        return length1 - index1;
    }

    if (word1[index1] == word2[index2])
    {
        return getMinDistance(word1, word2, index1 + 1, index2 + 1);
    }

    int distanceDelete = 1 + getMinDistance(word1, word2, index1 + 1, index2);
    int distanceReplace = 1 + getMinDistance(word1, word2, index1 + 1, index2 + 1);
    int distanceInsert = 1 + getMinDistance(word1, word2, index1, index2 + 1);

    return min(distanceDelete, min(distanceReplace, distanceInsert));
}

int EditDistance::getMinDistance2(string& word1, string& word2)
{
    int length1 = word1.length();
    int length2 = word2.length();

    if (length1 == 0)
    {
        return length2;
    }

    if (length2 == 0)
    {
        return length1;
    }

    vector<vector<int>> matrix(length1, vector<int>(length2));
    matrix[0][0] = word1[0] == word2[0] ? 0 : 1;
    for (int i = 1; i < length2; i++)
    {
        if (word1[0] == word2[i])
        {
            matrix[0][i] = i;
        }
        else
        {
            matrix[0][i] = min(matrix[0][i - 1], i + 1) + 1;
        }
    }

    for (int i = 1; i < length1; i++)
    {
        if (word1[i] == word2[0])
        {
            matrix[i][0] = i;
        }
        else
        {
            matrix[i][0] = min(matrix[i - 1][0], i + 1) + 1;
        }
    }

    for (int row = 1; row < length1; row++)
    {
        for (int col = 1; col < length2; col++)
        {
            if (word1[row] == word2[col])
            {
                matrix[row][col] = matrix[row - 1][col - 1];
            }
            else
            {
                matrix[row][col] = min(matrix[row - 1][col - 1], min(matrix[row][col - 1], matrix[row - 1][col])) + 1;
            }
        }
    }

    return matrix[length1 - 1][length2 - 1];
}

