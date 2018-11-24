#include <fstream>
#include <string>
#include <vector>

std::vector<int> prefix(const std::string& str)
{
    std::vector<int> pi(str.size());

    size_t k = 0;
    for (size_t i = 1; i < str.size(); ++i) {
        while (k > 0 && str[i] != str[k])
            k = pi[k - 1];

        if (str[k] == str[i])
            ++k;
        pi[i] = k;
    }

    return pi;
}

std::vector<int> match(const std::string& str, const std::string& pattern)
{
    std::vector<int> matches;
    auto pi = prefix(pattern);

    size_t k = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        while (k >= pattern.length() || (k > 0 && str[i] != pattern[k]))
            k = pi[k - 1];

        if (str[i] == pattern[k])
            ++k;
        if (k == pattern.size()) 
            matches.push_back(i - pattern.size() + 1);
    }

    return matches;
}

// Test code
int main()
{
    std::ifstream fin("strmatch.in");
    std::ofstream fout("strmatch.out");

    std::string str, pattern;
    fin >> pattern >> str;

    auto matches = match(str, pattern);

    fout << matches.size() << "\n";
    auto N = std::min(static_cast<int>(matches.size()), 1000);
    for (auto i = 0; i < N; ++i)
        fout << matches[i] << " ";
    fout << "\n";

    return 0;
}
