#include <cassert>
#include <iostream>
#include <algorithm>
//---------------------------------------------------------
// works the same way people sort a hand of cards:
// - we start with an with an empty left hand, and the cards face down on the table
// - we then remove one card at a time from the table, and insert it into 
// the correct position into the left hand.
// - to find the correct position of a card, we compare it with each of the
//   cards already in the hand, from left to right.
// - at all time, the cards held in the left hand are sorted,
//   and these cards were originally the top cards of the pile on the table.
//---------------------------------------------------------
//                       unsorted
//                     j ---------->
//          sorted
//         <-------i 
//     A [ <k|   |>k | k |   |   |   ] size
// k=key (current card)
//---------------------------------------------------------
//as in "introduction to algorithms"
void insertion_sort_00(int* A, int len)
{
	for(int j=1; j<len; ++j)
	{
		int i=j-1;
		int key=A[j]; //backup (as A[j] will be overwritten)
		//-----------------------------------------
		//shift all A[i]>key elements to the right by 1 slot
		//so that the key (A[j]) at it's proper place
		while(i>=0 && A[i]>key)
		{
			A[i+1]=A[i];	//shift 1 slot to the right
					//key will be erased ultimately (on 1st iteration i+1=j)
			--i;
		}
		//-----------------------------------------
		A[i+1]=key; //place the key at it's proper place
	}
}
//---------------------------------------------------------
//using swaps
void insertion_sort_01(int* A, int size)
{
	for(int j=1; j<size; ++j)
	{
		int i=j-1;
		int key=A[j]; //backup (as A[j] will be overwritten)
		//-----------------------------------------
		//shift all A[i]>key elements to the right by 1 slot
		//so that the key (A[j]) at it's proper place
		while(i>=0 && A[i]>key)
		{
			std::swap(A[i+1], A[i]);
			--i;
		}
	}
}
//---------------------------------------------------------
// cf binary insertion sort
//---------------------------------------------------------
int main()
{
	{
		int a[]={ 5, 2, 4, 0, 1, 3 };

		insertion_sort_00(a, 6);
		//insertion_sort_01(a, 6);

		for(int i=0; i<6; ++i)
			assert(a[i]==i);
	}
}
