



#include <iostream>
#include <stdio.h>
#define MAX 100

using namespace std;

int main(){
    int p[MAX+1]{0,};
    int r[MAX+1]{0,};
    int s[MAX+1]{0,};
    int print[MAX+1]{0,};
    
    int N;
    cin>>N;
    
    for(int i=1; i<=N; i++){
        scanf("%d", p+i);
    }
    
    for(int i=1; i<=N; i++){
        int max=0;
        
        for(int j=1; j<=i; j++){
            
            if(max<p[j]+r[i-j]){
                max=p[j]+r[i-j];
                s[i]=j;
            }
        }
        
        r[i]=max;
    }
    
    cout<<r[N]<<endl;
    
    int tmp=N;
    int index=0;
    while(tmp>0){
        print[index]=s[tmp];
        tmp-=s[tmp];
        index++;
    }
    
    for(int i=0; i<index-1; i++){
        for(int j=i+1; j< index; j++){
            if(print[i]>print[j]){
                int temp=print[i];
                print[i]=print[j];
                print[j]=temp;
            }
        }
    }
    
    for(int i=0; i<index; i++){
        printf("%d ", print[i]);
    }
    printf("\n");
    
    return 0;
}
