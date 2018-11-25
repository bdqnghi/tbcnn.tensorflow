#include <Rcpp.h>
#include <math.h>
using namespace Rcpp;




















int binary_search_cpp(double x, NumericVector y) {
  int startIdx = 0;
  int endIdx = y.size() - 1;

  while (startIdx <= endIdx) {
    int midIdx = (startIdx + endIdx) >> 1;
    double midVal = y[midIdx];

    if (midVal < x) {
      startIdx = midIdx + 1;
    } else if (midVal > x) {
      endIdx = midIdx - 1;
    } else if (fabs(x - midVal) < 1e-8) {
         return midIdx;
    }
  }
  return startIdx;
}








