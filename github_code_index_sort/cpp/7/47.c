#include "shellsort.h"
#include <algorithm>
using namespace std;

ShellSort::ShellSort(){

}

ShellSort::~ShellSort(){
}

std::string ShellSort::GetName(){
	return "ShellSort";
}

std::vector<int> ShellSort::Run(const std::vector<int>& data){
	std::vector<int> result = data;
	int h = 1;
	while( h < data.size()/3 ){
		h = 3 *h +1;
	}
	while( h >= 1 ){
		for( int i = h ;i < result.size();i++){
			int data = result[i];
			int j = i -h;
			for( ; j >= 0 ; j -= h ){
				if(result[j] > data ){
					result[j+h] = result[j];
				}else{
					break;
				}
			}
			result[j+h] = data;
		}
		h = h / 3;
	}
	
	return result;
}
