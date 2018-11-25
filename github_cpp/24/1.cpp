#include "std.h"



static mvalue bsearch(array &A, int v, int p, int r) {
  if (p < r) {
    int q = (p + r) / 2;
    if (v <= A[q])
      return bsearch(A, v, p, q);
    else
      return bsearch(A, v, q + 1, r);
  } else {
    mvalue result;
    if (A[p] == v)
      result = p;
    return result;
  }
}

static mvalue bsearch_iter(array &A, int v, int p, int r) {
  mvalue result;
  while (p <= r) {
    int q = (p + r) / 2;
    if (v == A[q]) {
      result = q;
      break;
    } if (v < A[q])
      r = q - 1;
    else if (v > A[q])
      p = q + 1;
  }
  return result;
}

mvalue bsearch(array &A, int v) {
  return bsearch_iter(A, v, 1, A.length);
}

