#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>

using namespace std;

#define interval 10 /* bucket range */
#define NBUCKET 5 /* bucket size */

struct Node 
{ 
	int data;  
	struct Node *next; 
};

void BucketSort(int arr[],int size);
struct Node *InsertionSort(struct Node *list);
void print(int arr[],int size);
void printBuckets(struct Node *list);
int getBucketIndex(int value);

void BucketSort(int arr[],int size)
{	
	int i,j;
	struct Node **buckets;  

	/* allocate memory for array of pointers to the buckets */
	buckets = (struct Node **)malloc(sizeof(struct Node*) * NBUCKET); 

	/* initialize pointers to the buckets */
	for(i = 0; i < NBUCKET;++i) {  
		buckets[i] = NULL;
	}

	/* put items into the buckets */
	for(i = 0; i < size; ++i) {	
		struct Node *current;
		int pos = getBucketIndex(arr[i]);
		current = (struct Node *) malloc(sizeof(struct Node));
		current->data = arr[i]; 
		current->next = buckets[pos];  
		buckets[pos] = current;
	}

	/* check what's in each bucket */
	for(i = 0; i < NBUCKET; i++) {
		cout << "Bucket[" << i << "] : ";
	        printBuckets(buckets[i]);
		cout << endl;
	}

	/* sorting bucket using Insertion Sort */
	for(i = 0; i < NBUCKET; ++i) {  
		buckets[i] = InsertionSort(buckets[i]); 
	}

	/* check what's in each bucket */
	cout << "-------------" << endl;
	cout << "Buckets after sorted" << endl;
	for(i = 0; i < NBUCKET; i++) {
		cout << "Bucket[" << i << "] : ";
	        printBuckets(buckets[i]);
		cout << endl;
	}

	/* put items back to original array */
	for(j =0, i = 0; i < NBUCKET; ++i) {	
		struct Node *node;
		node = buckets[i];
		while(node) {
			arr[j++] = node->data;
			node = node->next;
		}
	}
	
	/* free memory */
	for(i = 0; i < NBUCKET;++i) {	
		struct Node *node;
		node = buckets[i];
		while(node) {
			struct Node *tmp;
			tmp = node; 
			node = node->next; 
			free(tmp);
		}
	}
	free(buckets); 
	return ;
}

/* Insertion Sort */
struct Node *InsertionSort(struct Node *list)
{	
	struct Node *k,*nodeList;
	/* need at least two items to sort */
	if(list == 0 || list->next == 0) { 
		return list; 
	}
	
	nodeList = list; 
	k = list->next; 
	nodeList->next = 0; /* 1st node is new list */
	while(k != 0) {	
		struct Node *ptr;
		/* check if insert before first */
		if(nodeList->data > k->data)  { 
			struct Node *tmp;
			tmp = k;  
			k = k->next; 
			tmp->next = nodeList;
			nodeList = tmp; 
			continue;
		}

		for(ptr = nodeList; ptr->next != 0; ptr = ptr->next) {
			if(ptr->next->data > k->data) break;
		}

		if(ptr->next!=0){  
			struct Node *tmp;
			tmp = k;  
			k = k->next; 
			tmp->next = ptr->next;
			ptr->next = tmp; 
			continue;
		}
		else{
			ptr->next = k;  
			k = k->next;  
			ptr->next->next = 0; 
			continue;
		}
	}
	return nodeList;
}

int getBucketIndex(int value)
{
	return value/interval;
}

void print(int ar[],int size)
{	
	int i;
	for(i = 0; i < size; ++i) { 
		cout << setw(3) << ar[i]; 
	}
	cout << endl;
}

void printBuckets(struct Node *list)
{
	struct Node *cur = list;
	while(cur) {
		cout << setw(3) << cur->data;
		cur = cur->next;
	}
}

int main(void)
{	int n,i;
	 printf("Enter the size of array: ");
    scanf("%d",&n);
	int a[n];
    printf("\nEnter the array elements: ");
    
    for(i=0;i<n;++i)
        scanf("%d",&a[i]);
      

	cout << "Initial array" << endl;
	print(a,n);
	cout << "-------------" << endl;

	
	BucketSort(a,n); 
	cout << "-------------" << endl;
	cout << "Sorted array"  << endl;
	print(a,n); 
	getch();
	return 1;
}
