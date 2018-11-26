#include <cstdio>
#include <cstdlib>
#include <string.h>

#include <dynprog.h>
#include <timer.h>
#include <random_generator.h>

#define ROD_LENGTH 8

int main(int argc, char* argv[])
{ 
  	random_generator rg;
  	random_generator::seed();

	for (int len=2;len<=8;len++) {
		cout<<"rod length="<<len<<endl;

		int* result1 = new int[len+1];
		int* result2 = new int[len+1];
		int* result3 = new int[len+1];
		int* solution = new int[len+1];

	  	int rod_price[9] = { 0, 1, 5, 8, 9, 10, 17, 17, 20 };
	//	int rod_cost[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	//	int rod_cost[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
		int rod_cost[9] = {0,1,2,6,5,4,3,2,1};

		/*  recursive definition of the revenue function R*/
		int price1 = cut_rod_R(rod_price,rod_cost,len);
		cout<<"naive cut rod  revenue: "<<price1<<endl;
		
		/*bottom-up algorithm for the alternate rod-cutting problem*/
		int price2 = bottom_up_cut_rod_R(rod_price,rod_cost,len,result1);
		cout<<"bottom up cut rod revenue: "<<price2<<endl;
		
		/*top-down algorithm with memoization for the alternate rod-cutting problem*/
		int price3 = memorized_cut_rod_R(rod_price,rod_cost,len,result2);
		cout<<"memorized cut rod revenue: "<<price3<<endl;
		
		/*reconstruct and print the solution*/
		print_cut_rod_solution(rod_price,rod_cost,len,result3,solution);
		cout<<endl;

		delete result1;
		delete result2;
		delete result3;
		delete solution;
				
	}

  	return 0;
}
  
