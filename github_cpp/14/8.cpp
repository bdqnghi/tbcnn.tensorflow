






#include "book.h"


#include "compare.h"

extern int THRESHOLD;

int POW2[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};

#define pow2(X) POW2[X]

template <typename E, typename getKey>
void radix(E A[], E B[],
           int n, int k, int r, int cnt[]) {
  
  int j;

  for (int i=0, rtoi=1; i<k; i++, rtoi*=r) { 
    for (j=0; j<r; j++) cnt[j] = 0;        

    
    for (j=0; j<n; j++) cnt[(getKey::key(A[j])/rtoi)%r]++;

    
    for (j=1; j<r; j++) cnt[j] = cnt[j-1] + cnt[j];

    
    
    for (j=n-1; j>=0; j--)
      B[--cnt[(getKey::key(A[j])/rtoi)%r]] = A[j];

    for (j=0; j<n; j++) A[j] = B[j];    
  }
}


template <typename E, typename Comp>
void sort(E* array, int n) {
  static E* temp = NULL;
  static int* cnt = NULL;
  Assert(THRESHOLD > 0, "Need to set THRESHOLD");
  if (temp == NULL) temp = new E[n];  
  if (cnt == NULL) cnt = new int[pow2(THRESHOLD)];  
  radix<E,Comp>(array, temp, n, (sizeof(E) * 8)/THRESHOLD,
                   pow2(THRESHOLD), cnt);
}

#include "sortmain.cpp"

int main(int argc, char** argv) {
  return sortmain<getintKey>(argc, argv);
}
