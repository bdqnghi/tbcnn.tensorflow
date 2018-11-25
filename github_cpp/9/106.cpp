#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class StringReverse {
public:
    StringReverse() {}
    ~StringReverse() {}
    void Run(void) {
        char *str = "a test string";
        char buf[100];
        Copy(buf, str);
        printf("%s\n", buf);
        ReverseWords(buf);
        printf("%s\n", buf);
    }

    void Reverse(char * str, int start, int length) {
        if (str == NULL) return;
        char c = 0;
        char *tail = str;
        while (*tail){
            tail += 1;
        }
        if (tail > str + start + length) tail = str + start + length;
        for (str= str + start, tail -= 1; str < tail; str++, tail--) {
            c = *tail;
            *tail = *str;
            *str= c;
        }
    }

    void ReverseWords(char * str) {
        if (str == NULL) return;
        int start = 0, end = 0;
        bool startFind = true;
        char * head = str;
        while (*str) {
            if (*str == ' ') {
                if (startFind) {
                    Reverse(head, start, end - start);
                }
                else {
                    startFind = true;
                }
                start = end + 1;
            }
            end += 1;
            str += 1;
        }
        Reverse(head, start, end - start);
    }
private:
    void Copy(char * target, char * source){
        while (*source) {
            *target++ = *source++;
        }
        *target = 0;
    }
};