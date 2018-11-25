
#include <bits/stdc++.h>

using namespace std;

void towerOfHanoi(int N, char BEG, char AUX, char END);

int main()
{
    int n;
    char BEG, AUX, END, dump;

    printf("Total disks = ");
    scanf("%d", &n);
    dump = getchar();
    printf("Beginning Tower = ");
    scanf("%c", &BEG);
    dump = getchar();
    printf("Auxiliary Tower = ");
    scanf("%c", &AUX);
    dump = getchar();
    printf("Ending Tower = ");
    scanf("%c", &END);

    printf("=== MOVES ===\n");
    towerOfHanoi(n, BEG, AUX, END);

    return 0;
}

void towerOfHanoi(int N, char BEG, char AUX, char END)
{
    if (N == 1) {
        printf("%c -> %c\n", BEG, END);
        return;
    }

    towerOfHanoi(N - 1, BEG, END, AUX);
    printf("%c -> %c\n", BEG, END);

    towerOfHanoi(N - 1, AUX, BEG, END);
}
