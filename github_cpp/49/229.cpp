#include <stdio.h>
#include <iostream>
#include "../include/common.hpp"
#include <stdlib.h>
#include "../include/Linear_Regression.hpp"

namespace Arsenal{
template <typename Dtype>
void Linear_Regression<Dtype>::Forward(){
	this->output.MV_multiply(false, this->input, this->weight, this->output, this->_Num_samples, this->_dimension);
	this->output.MM_add(this->output, this->bias, this->output);
}

template <typename Dtype>
void Linear_Regression<Dtype>::Test(){
	//int accu[3];
	Forward();
	//accu = this->output.Accuracy(this->output, this->labels);
}

template <typename Dtype>
void Linear_Regression<Dtype>::Backward(){
	_bgd.Linear_Regression_bgd(this->labels, this->output, this->weight, this-> bias, this->input);	
}

template <typename Dtype>
void Linear_Regression<Dtype>::Train(){
	Backward();
}


template <typename Dtype>
void Linear_Regression<Dtype>::Dataset_get(Mat<Dtype> input_get, Mat<Dtype> labels_get){	
	this->input.Copy(input_get);
	this->labels.Copy(labels_get);
}

INSTANCE_CLASS(Linear_Regression);
}
