#include <iostream>


using namespace std;

void qsort(int[],int,int);
int adjustArr(int[],int,int);
void quickSort(int[],int,int);
int main(){
	int arr[13] = {13,5,78,2,5,8,44,47,4,32,46,2,12};
	int s =0;
	int r = sizeof(arr)/sizeof(int);
	cout<<"len is "<<r<<endl;
	quickSort(arr,0,r);
	//qsort(arr,0,r-1);
	for(int i=0;i<r;i++){
		cout<<arr[i]<<endl;
	}

}

int ii = 0;
int adjustArr(int arr[],int s,int r){

	cout<<"step: "<<ii++<<endl;
	int start = arr[s];
	while(s<r){
		while(s<r && arr[r]>start){
			r--;
		}
		if(s<r){
			arr[s++]  = arr[r];
		}

		while(s<r && arr[s]<start){
			s++;
		}
		if(s<r){
			arr[r--] = arr[s];
		}

	}
	arr[r] = start;
	return r;
}

void quickSort(int arr[],int s,int r){
	if(s>=r)return;
	int i = adjustArr(arr,s,r);
	quickSort(arr,s,i-1);
	quickSort(arr,i+1,r);
	
}

void qsort(int s[], int l, int r)
{
    int i, j, x;
    if (l < r)
    {
        i = l;
        j = r;
        x = s[i];
        while (i < j)
        {
            while(i < j && s[j] > x) j--; /* 从右向左找第一个小于x的数 */
            if(i < j) s[i++] = s[j];
            while(i < j && s[i] < x) i++; /* 从左向右找第一个大于x的数 */
            if(i < j) s[j--] = s[i];
        }
        s[i] = x;
        qsort(s, l, i-1); /* 递归调用 */
        qsort(s, i+1, r);
    }
}










