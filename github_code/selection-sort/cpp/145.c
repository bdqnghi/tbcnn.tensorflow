#include<stdio.h>
void selectionsort(int *a,int n){
    for (int i = 0; i <n-1 ; i++) {
        int min=a[i];
        int position;
        for (int k = 0; k < n; k++) {
            if (a[i]>a[k]) {
                min=a[k];
                position=k;
            }
        }
        if (a[i]!=min) {
            a[position]=a[i];
            a[i]=min;
        }
    }

}
int main(int argc, char const *argv[]) {
    int a[]={2,38,468,3,2,753,2,852,45,3,84};
    selectionsort(a,sizeof(a)/sizeof(int));
    for(int i=0;i<sizeof(a)/sizeof(int);i++){
    	printf("%d ",a[i]);
    }
    printf("\n");
    return 0;
}
