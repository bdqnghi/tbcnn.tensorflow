
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
