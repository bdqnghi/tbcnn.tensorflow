#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<fstream>
#include "stat.h"
#include "common.h"
/**

implements logistic regression
input: feature matrix and class
output: accuracy
@author Sandipan Sikdar

**/

void logistic_regression(arma::mat train, arma::vec y, arma::mat W, int train_size){
	int num_steps = 10000;
	double learning_rate = 0.00001,r=0.0;
	arma::mat X(train_size,train.n_cols);
	arma::mat error(X.n_rows,1);
	for(int i=0;i<train_size;i++){
		for(int j=0;j<train.n_cols;j++)
			X(i,j)=train(i,j);
	}
	
	while(num_steps>0){		
		arma::mat y_bar = W.t() * X.t();
		y_bar = activate_sigmoid(y_bar);
		for(int i=0;i<train_size;i++){ 
			error(i) = y(i) - y_bar(i);
		}
		arma::mat gradient = X.t() * error;
		gradient = mul_scalar(gradient,learning_rate);
		W = W + gradient;
		if(num_steps%1000==0)
			std::cout<< "Steps left: " << num_steps << std::endl;			
		num_steps--;
	}	
	std::cout << "learnt weights" << std::endl;
	display(W);
	int cc = 0,e_x=0;
	for(int i=train_size;i<train.n_rows;i++){
		r = 0.0;
		e_x++;
		for(int j=0;j<train.n_cols;j++)
			r+=W(j)*train(i,j);
		if(round(sigmoid(r))==y(i))
			cc++;
	}
		
	std::cout << "accuracy: " << (double)(cc)/e_x << std::endl;
}

int main(int argc, char *argv[]){
	arma::mat X = read_csv("test_data");
	arma::mat train = remove_col(X,-1);
	std::cout<< "split train matrix" << std::endl;
	std::cout<< "train " << train.n_rows << "," << train.n_cols << std::endl;
	arma::vec y = find_class(X);
	arma::mat W = fill_random(train.n_cols,1);
	std::cout << "Initialization done" << std::endl;
	int train_size = (int)(0.8*train.n_rows);
	logistic_regression(train,y,W,train_size); 
	return 0;
}
