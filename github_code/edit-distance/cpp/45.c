//
// Created by yifan on 11/6/16.
//

#include <iostream>
#include "LevenshteinDistance.h"

int LevenshteinDistance::min(int a, int b) {
    return a < b ? a : b;
}
int LevenshteinDistance::max(int a, int b) {
    return a > b ? a : b;
}

double LevenshteinDistance::calculate(vector<KeywordToken> v1, vector<KeywordToken> v2) {
    int size1 = v1.size();
    int size2 = v2.size();
    double cost = 100000.0;
    int temp = 0;
    double similarity = 0;
    int len1 = 0, len2 = 0;

    for (int i = 0; i < size1; i++) {
        len1 = v1[i].name.length();
        cost = 100000;
        for (int j = 0; j < size2; j++) {
            string s1 = v1[i].name;
            string s2 = v2[j].name;
            temp = DutCalculateStringDistance(s1, s2);
            if (temp < cost) {
                cost = temp;
                len2 = v2[j].name.length();
            }
        }
        similarity += (max(len1, len2) - cost) / max(len1, len2);
    }

    return similarity / max(size1, size2);
}

int LevenshteinDistance::DutCalculateStringDistance(string &str1, string &str2) {
    int max1 = str1.size();
    int max2 = str2.size();

    int **ptr = new int *[max1 + 1];
    for (int i = 0; i < max1 + 1; i++) {
        ptr[i] = new int[max2 + 1];
    }

    for (int i = 0; i < max1 + 1; i++) {
        ptr[i][0] = i;
    }

    for (int i = 0; i < max2 + 1; i++) {
        ptr[0][i] = i;
    }

    for (int i = 1; i < max1 + 1; i++) {
        for (int j = 1; j < max2 + 1; j++) {
            int d;
            int temp = min(ptr[i - 1][j] + 1, ptr[i][j - 1] + 1);
            if (str1[i - 1] == str2[j - 1]) {
                d = 0;
            } else {
                d = 1;
            }
            ptr[i][j] = min(temp, ptr[i - 1][j - 1] + d);
        }
    }

    cout << "**************************" << endl;
    for (int i = 0; i < max1 + 1; i++) {
        for (int j = 0; j < max2 + 1; j++) {
            cout << ptr[i][j] << " ";
        }
        cout << endl;
    }
    cout << "**************************" << endl;
    int dis = ptr[max1][max2];

    for (int i = 0; i < max1 + 1; i++) {
        delete[] ptr[i];
        ptr[i] = NULL;
    }

    delete[] ptr;
    ptr = NULL;

    return dis;
}