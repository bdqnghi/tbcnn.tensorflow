//this is my mergesort
//其中也用到了Use_for_quicksort类  但是不同于quicksort的是 这里是闭区间
//为了 适应这个题   这个mergesort可以求逆序数    然后mergesort内部 比较时用的是Use_for_quicksort类的store_one  因为quicksort用了compare
//以后其他题用的时候注意改过来

https://dsa.cs.tsinghua.edu.cn/oj/course.shtml?courseid=45 lighthouse测试通过

#define MAX_N 4000000

#include <stdio.h>
#include<iostream>
using namespace std;

long long int count=0;

class Use_for_quicksort{
	public:
		int compare;
		int store_one;
};

//quicksort algotithm
int quicksort(Use_for_quicksort *data,int low,int high){
	int partition(Use_for_quicksort *data,int low,int high);
	if ((high-low)<1){
		return 0;
	}
	
	int middle=partition(data,low,high-1);
	quicksort(data,low,middle);
	quicksort(data,middle+1,high);
	return 0;
}

int partition(Use_for_quicksort *data,int low,int high){
	int backup_low=low;
	int backup_high=high;
	Use_for_quicksort middle_data=data[low];
	for(;low<high;){
		for(;low<high;){
			if(data[high].compare>middle_data.compare){
				high=high-1;
			}else{
				data[low]=data[high];
				low=low+1;
				break;
			}
		}
		for(;low<high;){
			if(data[low].compare<middle_data.compare){
				low=low+1;
			}else{
				data[high]=data[low];
				high=high-1;
				break;
			}
		}
	}
	int middle=low;
	data[low]=middle_data;
	low=backup_low;
	high=backup_high;
	return middle;
}

//mergesort algotithm
int mergesort(Use_for_quicksort *data,int low,int high){
	int merge(int low,int middle,int high,Use_for_quicksort *data);
	if(high-low<1){
		return 0;
	}
	int middle=(low+high)/2;
	mergesort(data,low,middle);
	mergesort(data,middle+1,high);
	merge(low,middle,high,data);
	return 0;
}

int merge(int low,int middle,int high,Use_for_quicksort *data){
	int i = low;
	int j = middle + 1;
	int k = 0;
	Use_for_quicksort* temp = new Use_for_quicksort[high - low + 10];
	while(i <= middle && j <= high){
		if(data[i].store_one <= data[j].store_one){
			temp[k++] = data[i++];
		}else{
			temp[k++] = data[j++];
			count = count + middle + 1 - i;
		}
	}
	while(i <= middle){
		temp[k++] = data[i++];
	}
	while(j <= high){
		temp[k++] = data[j++];
	}
	for(i = low, k = 0; i <= high;){
		data[i++] = temp[k++];
	}
	delete []temp;
	return 0;
}

int main(){

    //输入
    long long int n;
    scanf("%d",&n);
    Use_for_quicksort* input = new Use_for_quicksort[MAX_N];
    int i; 
    for (i=0;i<n;i++){
		scanf("%d %d",&(input[i].compare),&(input[i].store_one));
		}
	//排序x
	quicksort(input,0,n); 
	//归并排序得逆序数
	mergesort(input,0,n-1);
	printf("%lld",(long long int)n*(n-1)/2-count);
    return 0;
}

