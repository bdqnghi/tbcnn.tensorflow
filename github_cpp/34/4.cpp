#include "NaiveBayes.h"

NaiveBayes::NaiveBayes() {
    this->model = new Model*[0];
    this->modelSize = 0;
}

NaiveBayes::~NaiveBayes() {
  for (int i = this->modelSize-1; i > 0; i--) {
    delete this->model[i];
  }
  delete this->model;
}


NaiveBayes* NaiveBayes::addModel(const uint8_t id, const double mean, const double standardDeviation) {
    int n = this->modelSize;
    Model** temp = new Model*[n+1];
    this->modelSize++;
    for(int i = 0; i < n; i++) {
        temp[i] = this->model[i];
    }
    temp[n] = new Model();
    temp[n]->id = id;
    temp[n]->mean = mean;
    temp[n]->standardDeviation = standardDeviation;

    Model** oldModel = this->model;
    this->model = temp;
    delete oldModel;
    
    return this;
}


void NaiveBayes::classify(Category categories[], const int numCategories, const double observations[], const int numObservations) {
    int n = this->modelSize;
    if(n != numCategories || n == 0) return;
    for(int i = 0; i < n; i++) {
        Model* category = this->model[i];
        categories[i].probability = 1.0 / n;
        for(int observationIndex = 0; observationIndex < numObservations; observationIndex++) {
            double value = observations[observationIndex];
            categories[i].probability *= (1.0/sqrt(2.0 * M_PI * category->standardDeviation)) * exp( (-pow(value - category->mean, 2)) / (2.0 * category->standardDeviation) );
        }
    }
}
