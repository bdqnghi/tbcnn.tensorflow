#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int SIZE = 10;

void bucketSort(int toSort[]);
void gathering(int toSort[], int bucket[][SIZE]);
void distribution(int toSort[], int bucket[][SIZE], int digitPos);
int getDigit(int n, int digitPos);
int digitsOfMax(int a[]);
void printArray(int a[]);
void resetBucket(int bucket[][SIZE]);

int main()
{
	int toSort[SIZE] = {4, 64, 656, 21, 77, 13, 903, 3322, 5, 80};

	cout << "before sorting: ";
	printArray(toSort);
	bucketSort(toSort);
	cout << "\nafter sorting: ";
	printArray(toSort);

	cout << endl << endl;
	return 0;
}

void bucketSort(int toSort[])
{
	int bucket[10][SIZE] = {0};
	int runTimes = digitsOfMax(toSort);

	int digitPos = 1;  //digitPos = 1, 10, 100, 1000...
	for(int i = 1; i <= runTimes; digitPos *= 10, i++) {
		distribution(toSort, bucket, digitPos);
		gathering(toSort, bucket);
		resetBucket(bucket);
	}
}

void distribution(int toSort[], int bucket[][SIZE], int digitPos)
{
	int digit;
	int place[10] = {0};  //10 buckets for 0~9 digit/bucket

	for(int i = 0; i < SIZE; i++) {
		digit = getDigit(toSort[i], digitPos);
		bucket[digit][place[digit]] = toSort[i];
		place[digit]++;  //record the index of 0~9 bucket
	}
}

void gathering(int toSort[], int bucket[][SIZE])
{
	int index = 0;
	for(int digit = 0; digit < 10; digit++) {
		for(int place = 0; place < SIZE; place++) {
			if(bucket[digit][place] != 0)
				toSort[index++] = bucket[digit][place];
			else 
				break;
		}
	}
}

int getDigit(int n, int digitPos)  //digitPos = 1, 10, 100, 1000...
{
	return (n % (digitPos*10)) / digitPos;
}

int digitsOfMax(int a[])
{
	int max = a[0];
	int digit = 1;

	//find the max number
	for(int i = 1; i < SIZE; i++) {
		if(a[i] > max)
			max = a[i];
	}

	//count the number of digit of max
	for(; max /= 10; digit++)
		;

	return digit;
}

void printArray(int a[])
{
	for(int i = 0; i < SIZE; i++)
		cout << a[i] << ' ';
}

void resetBucket(int bucket[][SIZE])
{
	for(int i = 0; i < 10; i++)
		for(int j = 0; j < SIZE; j++)
			bucket[i][j] = 0;
}