//quicksort和binary_search
//都使用专用的类Use_for_quicksort, 其中compare用于比较.
//quicksort与binary_search都为左闭右开型,即右边界是不被排序和搜索的
//binary_search里面的搜索失败返回值是视情况而定的,每次都要自己设定
//除此外  两个例子里面的函数都是一样的
//2017年2月13号再次在mooc的range里面使用  在range中对于不在数组中的点的情况需要特殊处理  这个以后还是根据具体情况处理  当前文件中的版本没有处理



//https://nanti.jisuanke.com/t/25测试有效
#include<iostream>
#include<cstdio>
using namespace std;

class Use_for_quicksort{
	public:
		int compare;
		int store_one;
};

int main(){
	int quicksort(Use_for_quicksort *data,int low,int high);
	int binary_search(Use_for_quicksort *data,int low,int high
	,int be_searched);
	int n;
	scanf("%d", &n);
	int store[510];
	Use_for_quicksort input[510];
	for(int i = 1; i < n + 1; i = i + 1){
		fscanf(stdin, "%d", &input[i].compare);
		store[i] = input[i].compare;
		input[i].store_one = i;
	}
	int target;
	scanf("%d", &target);
	//sort the input
	quicksort(input,1, n + 1);
	for(int i = 1; i < n + 1 ; i = i + 1){
		int temp = target - store[i];
		int result = binary_search(input, 1, n + 1, temp);
		if(-100 != result){
			printf("%d %d", i, input[result].store_one);
			break;
		}
	}
	return 0;
}

//二分查找
int binary_search(Use_for_quicksort *data,int low,int high
,int be_searched){
	
	for(;low<high;){
		int middle=(low+high)>>1;
		if(be_searched<data[middle].compare){
			high=middle;
		}
		else if(be_searched>data[middle].compare){
			low=middle+1;
		}
		else{
			for(;be_searched==data[middle].compare;middle=middle-1);
			middle=middle+1;
			return middle;
		}
	}
	return -100;
}

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































//https://dsa.cs.tsinghua.edu.cn/oj/course.shtml?courseid=45测试有效
#include<iostream>
#include<cstdio>
#include<malloc.h>
using namespace std;

class Use_for_quicksort{
	public:
		int compare;
		int store_one;
};

int k=0;
int main(){
	int quicksort(Use_for_quicksort *data,int low,int high);
	int find_the_height(int spot,int m,Use_for_quicksort*road);
	//输入
	static int n,m;
	fscanf(stdin,"%d %d",&n,&m);
	static Use_for_quicksort*road=(Use_for_quicksort*)malloc(1000100*sizeof(Use_for_quicksort));
	for(int i=0;i<m;i++){
		fscanf(stdin,"%d %d",&(road[i].compare),&(road[i].store_one));
	}
	//找出所有没有被指向的点,也就是可以作为起点的点
	int *find_origin=(int*)malloc(100100*sizeof(int));
	for(int i=0;i<100100;i++){
		find_origin[i]=0;
	}
	for(int i=0;i<m;i++){
		int temporary=road[i].store_one;
		find_origin[temporary]=temporary;
	}
	int *origin=(int *)malloc(100100*sizeof(int));
	int origin_number;//起点的个数(不含0)
	for(int i=1,j=0;i<=n;i++){
		if(0==find_origin[i]){
			origin[j++]=i;
			origin_number=j;
		}
	}
	//给路排序
	quicksort(road,0,m);
	//行动
	int number=0;
	for(int i=0;i<origin_number;i++){//一次循环,一个起点,一条路线
		int temporary=find_the_height(origin[i],m,road);
		if(temporary>number){
			number=temporary;
		}
	}
	//输出
	fprintf(stdout,"%d",number);
	return 0;
}

int find_the_height(int spot,int m,Use_for_quicksort*road){
	int binary_search(Use_for_quicksort *data,int low,int high,
	int be_searched);
	int length=0;
	int sign=9;
	int result=binary_search(road,0,m,spot);
	for(int i=result;i<m;i++){
		if(spot==road[i].compare){
			int temporary=find_the_height(road[i].store_one,m,road);
			if(temporary>length){
				length=temporary;
			}
			sign=10;
		}else{
			break;
		}
	}
	if(9==sign){
		return 1;
	}
	if(10==sign){
		return length+1;
	}
}

//二分查找
int binary_search(Use_for_quicksort *data,int low,int high
,int be_searched){
	
	for(;low<high;){
		int middle=(low+high)>>1;
		if(be_searched<data[middle].compare){
			high=middle;
		}
		else if(be_searched>data[middle].compare){
			low=middle+1;
		}
		else{
			for(;be_searched==data[middle].compare;middle=middle-1);
			middle=middle+1;
			return middle;
		}
	}
	return 10000010;
}

//快速排序
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
