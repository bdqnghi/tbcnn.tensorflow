

#include <stdio.h>

void towerOfHanoi(int n, char from, char to, char aux)  {
    if (n == 1) {
        printf("Move Disk 1 from %c to %c\n", from, to);
        return;
    }

    towerOfHanoi(n - 1, from, aux, to);
    printf("Move Disk %d from %c to %c\n", n, from, to);
    towerOfHanoi(n - 1, aux, to, from);
}

int main()  {
    towerOfHanoi(3, 'A', 'C', 'B');
    return 0;
}
