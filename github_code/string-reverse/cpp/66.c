#include <string>
#include <utility>

// More "C++"ey way of doing it.
std::string reverseString(std::string s) {
    if (s.size() > 1) {
        std::string::iterator start = s.begin(), end = --s.end();
        while (start < end) {
            std::swap(*start++, *end--);
            ++start, --end;
        }
    }
    
    return std::move(s);
}

// More "C"ey way of doing it.
// Inline swap with no temp value done using bitwise XOR.
std::string reverseStringInlineSwap(std::string s) {
    const int& length = s.size();
    if (length > 1) {
        for (int i = 0; i < length/2; i++) {
            s[i] ^= s[length - i-1];
            s[length - i-1] ^= s[i];
            s[i] ^= s[length - i-1];
        }
    }

    return std::move(s);
}

int main() {
    std::string hello = "hello";
    std::string olleh = reverseString(hello);
    
    std::cout << hello << " reversed is " << olleh << std::endl;
}
