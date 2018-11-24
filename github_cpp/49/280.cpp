/* 
 * File:   LinearRegression.cpp
 * Author: rodrigo
 * 
 * Created on 4 de Novembro de 2015, 10:42
 */

#include <string>
#include "LinearRegression.h"
#include "Logger.h"

LinearRegression::LinearRegression(float learning_rate, float regularization_factor, int hash_size) 
{
    alpha = learning_rate;
    lambda = regularization_factor;
    hash_space = hash_size;
    helper_sum = new float[hash_space];
    weights = new float[hash_space];
}

void LinearRegression::train(int epochs, training_data * x)
{
    int rows = x->length;
    float cost_function = 0;
    for(int epoch =1; epoch<= epochs; epoch++)
    {        
        for(int row = 0; row< rows; row++)
        {
            training_instance * instance = x->instances + row;
            float y = *(x->values + row);
            float prediction = predict(instance);
            float instance_error = prediction - y;
            
            cost_function += instance_error * instance_error;
            
            update(instance, instance_error);
        }
        
        weights[0] = weights[0] - (alpha/rows*helper_sum[0]); //biased term
        
        float weights_cost = 0;
        for(auto iterator = used_indices.begin(); iterator != used_indices.end(); iterator ++)
        {
            int index = * iterator;            
            weights_cost += weights[index] * weights[index];
            weights[index] = weights[index] * (1-alpha*lambda/rows) - (alpha*helper_sum[index]/rows);            
        }  
        
        cost_function += lambda * weights_cost;
        cost_function = cost_function/(2*rows);
        
        char text[80];
        sprintf(text, "Epoch = %d ; Cost Function = %f",epoch,cost_function);
        
        Logger::Log(std::string(text));
        helper_sum = new float[hash_space];        
    }
}

void LinearRegression::update(training_instance * instance, float instance_prediction_error)
{
    helper_sum[0] = instance_prediction_error;//biased term
    for(int i = 0; i < instance->features->size(); i++ )
    {
        int index = hash_trick(instance->features[i]);
        helper_sum[index] += instance_prediction_error * instance->feature_values[index];
        used_indices.insert(index);
    }
}

float LinearRegression::predict(training_instance * x)
{
    float result = weights[0];//biased term
    for(int i = 0; i < x->features->size(); i++ )
    {
        int index = hash_trick(x->features[i]);
        result += weights[index] * x->feature_values[index];
    }
    return result;
}
int LinearRegression::hash_trick(std::string feature)
{
    return std::hash<std::string>()(feature) % hash_space;
}
LinearRegression::~LinearRegression() 
{
}

