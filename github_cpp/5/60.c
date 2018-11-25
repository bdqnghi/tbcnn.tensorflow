#include <cassert>
#include <vector>
#include <iostream>
#include <climits>
using namespace std;

#include "gtest/gtest.h"

void my_swap(int& i, int& j) {
	int tmp = i;
	i = j;
	j = tmp;
}

void insertion_sort(vector<int>& vec) {

	for (size_t i = 1; i < vec.size(); ++i) {
		size_t j = i;
		while (j>0 && vec[j - 1] > vec[j]) {
			my_swap(vec[j - 1], vec[j]); 
			--j;
		}
	}

}

void insertion_sort_test_helper(const vector<int>& exp_arr,
								vector<int> arr) { 
	insertion_sort(arr);
	EXPECT_EQ(exp_arr, arr);
}

TEST(insertionSortTester, t1) {
	insertion_sort_test_helper(
		{1,2},
		{2,1});
}

TEST(insertionSortTester, t2) {
	insertion_sort_test_helper(
		{-2,1},
		{-2,1});
}

TEST(insertionSortTester, t3) {
	insertion_sort_test_helper(
		{ -8, -1, 2, 10 },
		{ 2, -1, 10, -8 });
}

TEST(insertionSortTester, t4) {
	insertion_sort_test_helper(
		{ 0, 1, 2, 3, 4, 5, 6, 7 },
		{ 0, 4, 3, 2, 5, 7, 1, 6 });
}

TEST(insertionSortTester, t5) {
	insertion_sort_test_helper(
		{ 2 },
		{ 2 });
}
	
TEST(insertionSortTester, t6) {
	insertion_sort_test_helper(
		{ -3, -2, 1 },
		{ -2, 1, -3 });
}

TEST(insertionSortTester, t7) {
	insertion_sort_test_helper(
		{ -8, -1, 2, 10, 500 },		
		{ 2, -1, 10, -8, 500 });
}

TEST(insertionSortTester, t8) {
	insertion_sort_test_helper(
		{ 0, 1, 2, 3, 5, 6, 7 },
		{ 0, 3, 2, 5, 7, 1, 6 });
}

TEST(insertionSortTester, t9_limits) {
	insertion_sort_test_helper(
	{ INT_MIN, 0, 1, 2, 3, 5, 6, 7, INT_MAX },	
	{ 0, 3, INT_MIN, 2, 5, INT_MAX, 7, 1, 6 });
}

TEST(insertionSortTester, t10_empty) {
	insertion_sort_test_helper(
	{},	
	{});
}


