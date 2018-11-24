#include <stdio.h>
#include <conio.h>
#include <fstream.h>
#include <string.h>
#include <time.h>
using namespace std;
int next[100000];
void init(char *p) {
    int i, j, M;
    next[0] = -1;
    M = strlen(p);
    for(i = 0, j = -1; i < M; i++, j++, next[i] = j)
      while((j >= 0) && (p[j] != p[i])) j = next[j];
}    
int kmp(char *a, char *p) {
    int i, j, M, N;
    M = strlen(p);
    N = strlen(a);
    init(p);
    
    for(i = 0, j = 0; j < M && i < N; i++, j++)
      while((j >= 0) && (p[j] != a[i])) j = next[j];
    if(j == M) return i-M; else return i;
}
int obicno(char *a, char *p) {
    int i, j, M, N;
    M = strlen(p);
    N = strlen(a);
    for(i = 0, j = 0; j < M && i < N; i++, j++)
      while((p[j] != a[i])) {i-= j -1; j = 0;}
    if(j == M) return i-M; else return i;
}        
int main() {
    ifstream in ("kmp.txt", ios::in);
    char str[100000], pat[100000];
    in >> str;
    in >> pat;
    //scanf("%s %s", str, pat);
    long double start = clock();
    printf("%d - (%0.18llf s)", kmp(str, pat), (start-clock())/1000);
    long double start2 = clock();
    printf("%d - (%0.18llf s)", obicno(str, pat), (start2-clock())/1000);
    
    getch();
    return 0;
}    
