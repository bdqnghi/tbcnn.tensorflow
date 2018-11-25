







#include <iostream>
using namespace std;


int Fibonacci_Recursive(int n);
int Fibonacci_Helper(int n, int map[]);
int Fibonacci_DP(const int n);
void initArray(int *arr, int size);




int Fibonacci_Recursive(int n) {
    if (n == 0 || n == 1)
        return 1;
    return Fibonacci_Recursive(n-1) + Fibonacci_Recursive(n-2);
}



int Fibonacci_Helper(int n, int* map) {

    if (map[n] == 0) {
        map[n] = Fibonacci_Helper(n-1, map) + Fibonacci_Helper(n-2, map);
    }
    
    return map[n];
}

int Fibonacci_DP(int n) {
    int *map = new int[n];
    initArray(map, n);
    map[0] = 1;
    map[1] = 1;
    int r = Fibonacci_Helper(n, map);
    free(map);  
    return r;
}




int RodCutting_Recursive (int len) ;
int RodCutting_Helper(int len, const int p[]);
int RodCutting_DP_Helper(int len, const int* p, int *map);
int RodCutting_DP(int len);


void initArray(int *arr, int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = 0;
}

int RodCutting_Recursive (int len) {

    int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    
    return RodCutting_Helper(len, p);
}

int RodCutting_Helper(int len, const int* p) {
    int r = p[len];
    
    if (len <= 0)
        return 0;
    
    if (len == 1)
        return 1;
    
    for (int i = 1; i <= len/2; ++i) {
        r = max(r, RodCutting_Helper(i, p)+RodCutting_Helper(len-i, p));
    }
    
    return r;
}


int RodCutting_DP(int len) {
    int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int *map = new int[len+1];
    initArray(map, len+1);
    map[0] = 0;
    map[1] = 1;
    
    int r = RodCutting_DP_Helper(len, p, map);
    
    free(map);
    return r;
}

int RodCutting_DP_Helper(int len, const int* p, int *map) {
    int r = p[len];
    
    if (len == 0 || len == 1 || map[len] != 0)
        return map[len];

    for (int i = 1; i <= len/2; ++i) {
        r = max(r, RodCutting_DP_Helper(i, p, map)+RodCutting_DP_Helper(len-i, p, map));
    }
    
    map[len] = r;
    
    return r;
}


int RodCutting_DP_BU(int len){
    int *map = new int(len+1);
    initArray(map, len+1);
    map[0] = 0;
    map[1] = 1;
    
    for (int i = 1; i <= len; ++i) {
        int t = 0;
        for (int j = 1; j <= i; ++j) {
            t = max(t, map[j]+map[i-j]);
        }
        map[i] = t;
    }
    
    int r = map[len];

    free(map);
    return r;
}

bool isSubsequence(string s, string t) {
    if (s == "")
        return true;
    
    int slen = (int)s.length();
    int tlen = (int)t.length();
    int i = 0;
    int j = 0;
    
    
    while (i < slen-1 && j < tlen-1) {
        if (s[i] == t[j]) {
            i++;
            j++;
        } else {
            j++;
        }
    }
    
    return i == slen-1;
}


int main(int argc, const char * argv[]) {
    cout << RodCutting_DP_BU(10) << endl;
    return 0;
}
