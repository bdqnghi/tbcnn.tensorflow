







#include <iostream>
#include<algorithm> 
using namespace std; 
struct Node{ 
    int key; 
    struct Node *next; 
    Node(int _key){ 
        key=_key;next=NULL; 
    } 
}; 
Node *buck[10];
Node *tail[10];
void base_sort_LSD(int *a,int n){ 
    int k,i,Max,kth,high,low; 
    Node *p; 
 
    for(Max=a[0],i=1;i<n;i++)
    	Max=max(Max,a[i]); 
    memset(buck,0,sizeof(buck)); 
 
    for(low=1,k=0;high=low*10,low<Max;low*=10,k++){
        for(i=0;i<n;i++){
            kth=(a[i]%high)/low;
            p=new Node(a[i]);
            
            buck[kth]!=NULL ?tail[kth]->next=p,tail[kth]=p:buck[kth]=p,tail[kth]=p; 
        } 
        for(kth=0,i=0;kth<n;i++){
            while(buck[i]!=NULL){ 
                a[kth++]=buck[i]->key; 
                p=buck[i],buck[i]=buck[i]->next,delete p;
            } 
        } 
    } 
} 
int main(){ 
    int n=10; 
    int data[]={1000,50,80000,81000,3,26,467,6987,10953,2354}; 
    base_sort_LSD(data,n); 
    for(int i=0;i<n;i++) 
        printf("%d ",data[i]); 
} 