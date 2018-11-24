// linear-regression.cpp

#include "linear-regression.h"

using namespace std;

/* dJ/dthe = (1/m)*X'*(X*the-y)
   where X € Rmxn, the € Rnx1, y € Rmx1
   Results in derivative */
void computeDerivativeCostFunction(int m,
                                   int n,
                                   double * X,
                                   double * the,
                                   double * y,
                                   double * derivative){
  double * tmp = (double*)malloc(sizeof(double) * m);
  for (int i=0;i<m; i++)
    tmp[i] = y[i];
  // (X*the-y)
  cblas_dgemv(CblasRowMajor, CblasNoTrans, m, n, 1.0, X, n, the, 1, -1.0, tmp, 1);
  // partial results in y € Rmx1
  // (1/m)*X'y
  double oneOverM = 1.0/m;
  cblas_dgemv(CblasRowMajor, CblasTrans, m, n, oneOverM, X, n, tmp, 1, 0.0, derivative, 1);
  free(tmp);
}


// the := the - alpha * (dJ/dthe)
// results in the
void computeGradientDescent(int n, double alpha, double * derivative, double * the){
  cblas_daxpy(n, (-1.0*alpha), derivative, 1, the, 1);
}

/* Gradient descent over cost function (1/2m)*(X*theta - y).^2 
   Return the theta vector */
void trainLinearRegression(int m,
                             int n,
                             double * X,
                             double * y,
                             double alpha,
                             int numIter,
                             double * theta){
  double * derivative = (double*)malloc(sizeof(double) * n);
  int i;
  for (i=0; i< n; i++)
    theta[i]=0.0;

  for (i=0; i<numIter; i++){
    computeDerivativeCostFunction(m, n, X, theta, y, derivative);
    computeGradientDescent(n, alpha, derivative, theta);
  }
  free(derivative);
}

// A x B where A is 3x3 and B is 3x3
/*
bool compute3x3MatrixMult(double A[9], double B[9], double (&C)[9]){
  // call dgemm(transa, transb, m, n, k, alpha, a, lda, b, ldb, beta, c, ldc)
  // C := alpha*op(A)*op(B) + beta*C,
  cblas_dgemm(CblasRowMajor,  // result beginning first row (top row to bottom row)
              CblasNoTrans, // No transposition of A
              CblasNoTrans, // No transposition of B
              3, // Rows of A
              3, // Rows of B, Columns of A
              3, // Columns of B
              1, // scalar times A
              A, // fist matrix mxn
              3, // leading dimension of A (in our case row dimension)
              B, // second matric nxk
              3, // leading dimension of B (in our case row dimension)
              0, // scalar times C
              C, // matric of results
              3);  // leading dimension of C
  return true;
} */

// Evaluates: prediction = x'*theta
void evaluateInput(int n, double * x, double * theta, double result){
  
}

