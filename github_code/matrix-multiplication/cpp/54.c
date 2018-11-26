//
//  matrix_multiplication.h
//  nntest
//
//  Created by Tobias Domhan on 12/28/13.
//  Copyright (c) 2013 Tobias Domhan. All rights reserved.
//

#ifndef nntest_matrix_multiplication_h
#define nntest_matrix_multiplication_h

#include "data.h"

/**
 * C = alpha * AB + beta * C
 * matrix1: A
 * matrix2: B
 * result_matrix: C
 */
class MatrixMultiplication {
public:
  enum MatrixOp {NoTranspose, MatrixTranspose};
  
  MatrixMultiplication(Data* matrix1, Data* matrix2, Data* result_matrix,
                       MatrixMultiplication::MatrixOp matrix1_transpose = NoTranspose,
                       MatrixMultiplication::MatrixOp matrix2_transpose = NoTranspose,
                       double alpha = 1.0,
                       double beta = 0.0);
  
  void check_dimensions();
  
  virtual void execute() = 0;
  
protected:
  Data* m_matrix1;
  Data* m_matrix2;
  MatrixMultiplication::MatrixOp m_matrix1_transpose;
  MatrixMultiplication::MatrixOp m_matrix2_transpose;
  Data* m_result_matrix;
  double m_alpha;
  double m_beta;
};

class MatrixMultiplicationBasic : public MatrixMultiplication {
public:

  MatrixMultiplicationBasic(Data* matrix1, Data* matrix2, Data* result_matrix,
                       MatrixMultiplication::MatrixOp matrix1_transpose = NoTranspose,
                       MatrixMultiplication::MatrixOp matrix2_transpose = NoTranspose,
                       double alpha = 1.0,
                       double beta = 0.0) : MatrixMultiplication(matrix1,
                                                                  matrix2,
                                                                  result_matrix,
                                                                  matrix1_transpose,
                                                                  matrix2_transpose,
                                                                  alpha,
                                                                  beta) {};
  virtual void execute();
private:
  
};

class MatrixMultiplicationMKL :  public MatrixMultiplication {
public:
  
  MatrixMultiplicationMKL(Data* matrix1, Data* matrix2, Data* result_matrix,
                            MatrixMultiplication::MatrixOp matrix1_transpose = NoTranspose,
                            MatrixMultiplication::MatrixOp matrix2_transpose = NoTranspose,
                            double alpha = 1.0,
                            double beta = 0.0) : MatrixMultiplication(matrix1,
                                                                      matrix2,
                                                                      result_matrix,
                                                                      matrix1_transpose,
                                                                      matrix2_transpose,
                                                                      alpha,
                                                                      beta) {};
  
  virtual void execute();
  

private:
};


class MatrixElementwiseMultiplication {
public:
  MatrixElementwiseMultiplication(Data* matrix1, Data* matrix2, Data* result_matrix);
  
  void check_dimensions();
  
  virtual void execute();
  
protected:
  Data* m_matrix1;
  Data* m_matrix2;
  Data* m_result_matrix;
};



class UnaryMathOp {
public:
  virtual void execute(Data* matrix) const = 0;
  virtual ~UnaryMathOp() {};
private:
};

class UniformRandom : public UnaryMathOp {
public:
  UniformRandom(double max) : m_max(max) {};
  
  virtual void execute(Data* matrix) const;
private:
  double m_max;
};

/*
 * Fills in the range of [-scale, scale]
 * where scale = sqrt(3./fan_in)
 * and fan_in = num_channels * width * height
 */
class FanInScaleFiller : public UnaryMathOp {
public:
  FanInScaleFiller() {};
  
  virtual void execute(Data* matrix) const;
};

class SetConst : public UnaryMathOp {
public:
  SetConst(double value) : m_value(value) {};
  
  virtual void execute(Data* matrix) const;
private:
  double m_value;
};

class MatrixLog : public UnaryMathOp {
public:
  MatrixLog() {};
  
  virtual void execute(Data* matrix) const;
private:
};

class AllNegativeZero : public UnaryMathOp {
public:
  AllNegativeZero() {};
  
  virtual void execute(Data* matrix) const;
private:
  double m_value;
};


/**
 * Apply the softmax function, normalized row by row
 */
class SoftmaxRowByRow : public UnaryMathOp {
public:
  SoftmaxRowByRow() {};
  
  virtual void execute(Data* matrix) const;
private:
  double m_value;
};

class DualMathOp {
public:
  virtual void execute(Data* matrix1, Data* matrix2) const = 0;
  virtual ~DualMathOp() {};
private:
};


class MatrixAdd: public DualMathOp {
public:
  MatrixAdd() : m_factor(1.) {};
  MatrixAdd(double factor) : m_factor(factor) {};
  
  /**
   * A += factor * B
   */
  virtual void execute(Data* A, Data* B) const;
  virtual ~MatrixAdd() {};
private:
  double m_factor;
};


/**
 * Adds a vector row by row
 */
class PlusEqualRow: public DualMathOp {
public:
  virtual void execute(Data* matrix, Data* row) const;
  virtual ~PlusEqualRow() {};
private:
};

class AllNegativeZeroMasked : public DualMathOp {
public:
  AllNegativeZeroMasked() {};
  
  virtual void execute(Data* matrix, Data* mask) const;
private:
  double m_value;
};

class DataSum {
public:
  DataSum() {};
  
  virtual double execute(Data* matrix);
private:
};

class DataAbsSum {
public:
  DataAbsSum() {};
  
  virtual double execute(Data* matrix);
private:
};

//takes a matrix of probabilities and returns the max-prob predictions in one-hot encoding
class MaxProbabilityPrediction {
public:
  std::unique_ptr<Data> execute(Data* probabilities);
};

#endif
