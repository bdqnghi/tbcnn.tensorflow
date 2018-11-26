// Edit_Distance.cpp : Defines the entry point for the console application.
//
#include <vector>
#include <iostream>
#include <algorithm>

template <class T> unsigned int edit_distance(const T& s1, const T& s2)
{
    const size_t len1 = s1.size(), len2 = s2.size();
    std::vector<std::vector<unsigned int> > d(len1 + 1, std::vector<unsigned int>(len2 + 1));
    for(int i = 1; i <= len1; ++i) d[i][0] = i;
    for(int i = 1; i <= len2; ++i) d[0][i] = i;
    for(int i = 1; i <= len1; ++i)
        for(int j = 1; j <= len2; ++j)
            d[i][j] = std::min<> ( std::min<> (d[i - 1][j] + 1,d[i][j - 1] + 1), d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) );
    return d[len1][len2];
}

int main(int argc, char* argv[])
{
    std::string s1("ABCBDAB");
    std::string s2("BDCABA");
    std::cout << "edit distance between '"<<s1<<"' and '"<<s2<<"' = " << edit_distance(s1, s2) << std::endl;;
    return 0;
}
