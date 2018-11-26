#include <math.h>
#include <iostream>
#include "Mat.h"

Mat::Mat() : colCount(0) {
}

double Mat::get(unsigned int row, unsigned int col) {
  return this->data.at(row).at(col);
}

void Mat::set(unsigned int row, unsigned int col, double val) {
  this->data.at(row).at(col) = val;
}

vector< vector<double> >& Mat::getData() {
  return data;
}

unsigned int Mat::getRowCount() {
  return data.size();
}

unsigned int Mat::getColCount() {
  return colCount;
}

void Mat::resize(unsigned int rows, unsigned int cols) {
  vector<double> tmpl(cols, 1.0);
  data.resize(rows, tmpl);
  for(int i = 0; i < getRowCount(); i++) {
    data[i].resize(cols, 1.0);
  }
  this->colCount = cols;
}

template <typename T> void vectorElementSwap(vector<T>& target, unsigned int fIdx, unsigned int sIdx) {
  T r1 = target[fIdx], r2 = target[sIdx];
  target.assign(fIdx, r2);
  target.assign(sIdx, r1);
}

void Mat::swapRows(unsigned int fIdx, unsigned int sIdx) {
  vectorElementSwap(data, fIdx, sIdx);
}

void Mat::swapCols(unsigned int fIdx, unsigned int sIdx) {
  for(int i = 0; i < data.size(); i++) {
    vectorElementSwap(data.at(i), fIdx, sIdx);
  }
}

vector<double> Mat::getNormalizedEigenvalues() {
  vector<double> result, tmp;
  double colSum = 0.0;
  for(int row = 0; row < data.size(); row++) {
    double sum = 0.0;
    for(int col = 0; col < data.size(); col++) {
      sum += get(row, col);
    }
    colSum += sum;
    tmp.push_back(sum);
  }
  for(int row = 0; row < data.size(); row++) {
    result.push_back(tmp[row]/colSum);
  }
  return result;
}

vector<double> Mat::getCol(unsigned int idx) {
  vector<double> result(getRowCount());
  for(int i = 0; i < getRowCount(); i++) {
    result[i] = get(i, idx);
  }
  return result;
}


Mat Mat::operator*(Mat& right) {
  if(getRowCount() != getColCount()) throw "Matrix-multiplication with different dimensions not implemented!";
  Mat result;
  result.resize(getRowCount(), getColCount());
  for(int row = 0; row < getRowCount(); row++) {
    for(int col = 0; col < getColCount(); col++) {
      double sum = 0.0;
      for(int i = 0; i < getColCount(); i++) {
        sum += get(row, i) * right.get(i, col);
      }
      result.set(row, col, sum);
    }
  }
  return result;
}

vector<double> Mat::operator*(vector<double>& right) {
  if(getColCount() != right.size()) throw "Matrix-multiplication with different dimensions not implemented!";
  vector<double> result(getRowCount(), 0.0);
  
  for(int row = 0; row < getRowCount(); row++) {
    for(int col = 0; col < getColCount(); col++) {
      result[row] += get(row, col) * right[col];
    }
  }
  return result;
}
