/******************************************************
** This is a practice code for rod cutting problem:
** Assume r_n is the maximum profit for cutting the 
** rod of length n
** Recursive function:
**   r_n = max(p_i, r_{n-i}) with i from 1 to n
**
******************************************************/
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <string>
#include <sstream>
#include <assert.h>

using namespace std;

	
int rodCutting(vector<int>& prices){
    size_t n = prices.size();

    // initialize the DP array:
    vector<int> r(n+1, 0);

    for(size_t i = 1; i <= n; ++i){
        int q = INT_MIN;
	for(size_t j = 0; j < i; ++j){
	    q = max(q, prices[j] + r[i-j-1]);
        }
        r[i] = q;
    }
    return r[n];
}

int main(int argc, char ** argv){
    string str;
    while(getline(cin, str)){
        istringstream iss(str);
	int num;
	vector<int> p;
	while(iss>>num){
	    p.push_back(num);
	    assert(num >= 0);
	}
	int answer = p.back();
	p.pop_back();
	int my_answer = rodCutting(p);
	cout<<"Your answer: "<<my_answer<<"\tCorrect answer should be: "<<answer<<endl;
    }

}
