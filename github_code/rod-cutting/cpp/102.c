//2015005632_JANGHYEJEONG
#include <stdio.h>

int main(){
    int num;
    scanf("%d", &num);
    int p[num+1];
    for(int i=1; i<=num; i++)
        scanf("%d", &p[i]);
    int r[num+1], s[num+1];
    p[0] = 0;
    r[0] = 0;
    s[0] = 0;
    for(int i=1; i<=num; i++){
        int max = 0;
        for(int j=1; j<=i; j++){
            int r_can = p[j] + r[i-j];
            if (r_can > max){
                max = r_can;
                s[i] = j;
            }
        }
        r[i] = max;
    }
    printf("%d\n", r[num]);
    while(num>0){
        printf("%d ", s[num]);
        num = num-s[num];
    }
    return 0;
}

