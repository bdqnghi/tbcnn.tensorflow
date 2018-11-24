#include <iostream>

void generate_prefix(const char *prefix, int size, int *pi) {
    int j = 1;
    for(int i = 0; i < size; i++){
        if(prefix[i] == prefix[j]){
            pi[i] = j+1;
            j++;
        } else {
            while(j != 0 && prefix[i] != prefix[j]){
                j = pi[j-1];
            }
            pi[i] = j;
        }
    }
}

void search(const char *needle, const char *haystack, const int *pi, int pi_size, int full_size){
    int j = 0;
    for(int i = 0; i < full_size; i++){
        if(haystack[i] == needle[j]){
            j++;
        } else {
            while(haystack[i] != needle[j] && j > 0){
                j = pi[j - 1];
            }
        }

        if(j >= pi_size){
            std::cout << "match found at index " << i-j+1 << std::endl;
            j = pi[j - 1]; // can be set to 0 if you don't want to match overlapping occurrences of needle
        }
    }
}

int main() {

    const int size_needle = 6;
    const int size_haystack = 20;
    const char *needle = "ababbb";
    const char *haystack = "aaabaabababbbaaaabab";

    int pi[size_needle] = {0};

    generate_prefix(needle, size_needle, pi);
    search(needle, haystack, pi, size_needle, size_haystack);

    return 0;
}
