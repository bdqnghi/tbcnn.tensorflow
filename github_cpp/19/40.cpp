#include <memory>
#include <string>
#include <algorithm>
#include <vector>
#include <cassert>

#include "KnuthMorrisPratt.h"

/****************************************************************/
// http://www.geeksforgeeks.org/searching-for-patterns-set-2-kmp-algorithm/
// Knuth Morris Pratt string search.
typedef std::wstring::size_type ssize;
ssize kmp(const std::wstring &text, const std::wstring &pattern) {
	std::vector<ssize> offset(pattern.size(), 0);
	ssize p, t;
    for (t = 1, p = 0; t < pattern.size(); ++t) {
        if (pattern[t] == pattern[p]) offset[t] = ++p;
        else if (p) {
            p = offset[p - 1];
            --t; // Recompare character in next loop.
        }
    }
    t = p = 0;
	while (t < text.size() && p < pattern.size()) {
		while (text[t] == pattern[p]) {
			t++; p++; 
			if (p == pattern.size()) return t - p;
		}	
        if (!p || p == offset[p - 1]) t++;
        else p = offset[p - 1];
	}
	return text.size();
}
void test_kmp() {
    assert(7 == kmp(L"xxxxabcabcabdyyyyyy", L"abcabd"));
    assert(7 == kmp(L"日本日本日本語日本語日本人日本日本日本日本日本", L"日本語日本人"));
    assert(12 == kmp(L"zzzxxxzzzxxGzzzxxxzzzxxx", L"zzzxxxzzzxxx"));
    assert(24 == kmp(L"zzzxxxzzzxxGzzzxxxzzzxxx", L"zzzxxxzzzxxxX"));
    assert(1 == kmp(L"abcabcabc", L"b"));
    assert(19 == kmp(L"xxxxabcabcabdyyyyyy", L"abcabde"));
    assert(4 == kmp(L"xxxxabcabcabdyyyyyy", L"abcabcabd"));
    assert(0 == kmp(L"abc", L"abc"));
    assert(0 == kmp(L"", L""));
    assert(3 == kmp(L"abc", L""));
    assert(0 == kmp(L"", L"abc"));
}
/****************************************************************/