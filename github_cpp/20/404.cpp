#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <fstream>
#include "hmm.h"

#define USE_FIXED_DIGRAPH //enable this define to use a fixed A matrix from a pre-defined digraph
#ifdef USE_FIXED_DIGRAPH
#include "AMat.h"
#endif

#define MAX_INT 9223372036854775807

static const std::string ObserSet = "abcdefghijklmnopqrstuvwxyz";

HMM::HMM(int N, int M, int minIters, float epsilon)
{
   mN = N;
   mM = M;
   mMinIters = minIters;
   mEps = epsilon;
   mOldLogProb = -MAX_INT;

   mA = NULL;
   mB = NULL;
   mPI = NULL;

   mC = NULL;
   mAlpha = NULL;
   mBeta = NULL;
   mGamma = NULL;
   mDiGamma = NULL;
}
HMM::~HMM()
{
   freeTables();
}

void HMM::freeTables()
{
   if (mA) {
      free(mA);
      mA = NULL;
   }
   if (mB) {
      free(mB);
      mB = NULL;
   }
   if (mPI) {
      free(mPI);
      mPI = NULL;
   }
   if (mC) {
      free(mC);
      mC = NULL;
   }
   if (mAlpha) {
      free(mAlpha);
      mAlpha = NULL;
   }
   if (mBeta) {
      free(mBeta);
      mBeta = NULL;
   }
   if (mGamma) {
      free(mGamma);
      mGamma = NULL;
   }
   if (mDiGamma) {
      free(mDiGamma);
      mDiGamma = NULL;
   }
}

void HMM::printModel()
{
   printf("A = \n");
   for (int i = 0; i < mN; i++) {
      std::string msg = std::to_string(i) + ": ";
      for (int j = 0; j < mN; j++) {
         msg += std::to_string(*getA(i, j)) + " ";
      }
      printf("%s\n", msg.c_str());
   }
   printf("B = \n");
   for (int j = 0; j < mM; j++) {
      std::string msg = std::string(1, ObserSet[j]) + ": ";
      for (int i = 0; i < mN; i++) {
         msg += std::to_string(*getB(i, j)) + " ";
      }
      printf("%s\n", msg.c_str());
   }
   printf("PI = \n");
   std::string msg = "";
   for (int i = 0; i < mN; i++) {
      msg += std::to_string(*getPI(i)) + " ";
   }
   printf("%s\n", msg.c_str());
}

void HMM::fit(int* obserArr, int T)
{
   int iters = 0;
   float logProb = -MAX_INT;
   float diff = MAX_INT;
   setupTable(T);
   randomInit();
#ifndef _NO_MAIN
   printModel();
#endif
   while (iters < mMinIters || diff > mEps) {
      logProb = getScore(obserArr, T);
      backwardPass(obserArr, T);
      calcGammaDigamma(obserArr, T);
      reEstimateModel(obserArr, T);

      diff = std::abs(logProb - mOldLogProb); 
      mOldLogProb = logProb;

      //if (iters % 10 == 0) {
#ifndef _NO_MAIN
         printModel();
         printf("%d_score = %.3f\n========================================\n\n", iters, logProb);
#endif
      //}

      iters += 1;
   }

   printf("HMM trained\n");
#ifndef _NO_MAIN
   printModel();
#endif
   printf("%d_score = %.3f\n========================================\n\n", iters, logProb);
}

float HMM::getScore(int* obserArr, int T)
{
   forwardPass(obserArr, T);
   float logProb = 0;
   for (int t = 0; t < T; t++) logProb += std::log(*(getC(t))); 
   return -logProb;
}

void HMM::setupTable(int T)
{
   freeTables();

#ifndef USE_FIXED_DIGRAPH
   mA = (float*)malloc(mN*mN*sizeof(float));
   if (!mA) {
      printf("No memory!\n");
      exit(-1);
   }
#endif

   mB = (float*)malloc(mN*mM*sizeof(float));
   if (!mB) {
      printf("No memory!\n");
      exit(-1);
   }
   mPI = (float*)malloc(mN*sizeof(float));
   if (!mPI) {
      printf("No memory!\n");
      exit(-1);
   }

   mC = (float*)malloc(T*sizeof(float));
   if (!mC) {
      printf("No memory!\n");
      exit(-1);
   }
   mAlpha = (float*)malloc(T*mN*sizeof(float));
   if (!mAlpha) {
      printf("No memory!\n");
      exit(-1);
   }
   mBeta = (float*)malloc(T*mN*sizeof(float));
   if (!mBeta) {
      printf("No memory!\n");
      exit(-1);
   }
   mGamma = (float*)malloc(T*mN*sizeof(float));
   if (!mGamma) {
      printf("No memory!\n");
      exit(-1);
   }
   mDiGamma = (float*)malloc(T*mN*mN*sizeof(float));
   if (!mDiGamma) {
      printf("No memory!\n");
      exit(-1);
   }
}
float HMM::getRandVal(int k)
{
   float r = float(rand())/RAND_MAX;
   float v = 1.0/k; 
   float delta = 0.1 * v;
   return v + -delta + (r * 2 * delta);
} 

void HMM::normalizeArr(float* arr, int T)
{
   float sum = 0;
   for (int idx = 0; idx < T; idx++) sum += arr[idx];
   if (sum == 0) {
      printf("error! can't normalize all 0\n");
      exit(-1);
   }
   for (int idx = 0; idx < T; idx++) arr[idx] /= sum;
}
void HMM::randomInit()
{
   srand(time(NULL));

#ifndef USE_FIXED_DIGRAPH
   for (int idx = 0; idx < mN; idx++) {
      for (int jdx = 0; jdx < mN; jdx++) {
         *getA(idx, jdx) = getRandVal(mN);
      }
      normalizeArr(mA+(idx*mN), mN);
   }
#endif

   for (int idx = 0; idx < mN; idx++) {
      for (int jdx = 0; jdx < mM; jdx++) {
         *getB(idx, jdx) = getRandVal(mM);
      }
      normalizeArr(mB+(idx*mM), mM);
   }
   for (int idx = 0; idx < mN; idx++) {
      *getPI(idx) = getRandVal(mN);
   }
   normalizeArr(mPI, mN);
} 

void HMM::forwardPass(int* obserArr, int T)
{
   //compute a0[i]
   *getC(0) = 0;
   for (int idx = 0; idx < mN; idx++) {
      float _a = (*getPI(idx)) * (*getB(idx, obserArr[0])); 
      *getAlpha(0, idx) = _a;
      *getC(0) = (*getC(0)) + _a;
   }

   //scale the a0(i)
   *getC(0) = 1.0 / (*getC(0));
   for (int idx = 0; idx < mN; idx++) {
      *getAlpha(0, idx) = (*getAlpha(0, idx)) * (*getC(0));
   }

   //compute at(i)
   for (int t = 1; t < T; t++) {
      *getC(t) = 0;
      for (int idx = 0; idx < mN; idx++) {
         *getAlpha(t, idx) = 0;
         for (int jdx = 0; jdx < mN; jdx++) {
            *getAlpha(t, idx) = (*getAlpha(t, idx)) +  ((*getAlpha(t-1, jdx)) * (*getA(jdx, idx)));
         }
         *getAlpha(t, idx) = (*getAlpha(t, idx)) * (*getB(idx, obserArr[t]));
         *getC(t) = (*getC(t)) + (*getAlpha(t, idx));
      }

      //scale at(i)
      *getC(t) = 1.0 / (*getC(t));
      for (int idx = 0; idx < mN; idx++) {
         *getAlpha(t, idx) = (*getAlpha(t, idx)) * (*getC(t));
      }
   }
}

void HMM::backwardPass(int* obserArr, int T)
{
   //let beta_t-1(i) = 1 scaled by cT-1
   for (int idx = 0; idx < mN; idx++) {
      *getBeta(T-1, idx) = *getC(T-1);
   }

   //beta-pass
   for (int t = T-2; t > 0; t--) {
      for (int idx = 0; idx < mN; idx++) {
         *getBeta(t, idx) = 0;
         for (int jdx = 0; jdx <mN; jdx++) {
            *getBeta(t, idx) += (*getA(idx, jdx) * (*getB(jdx, obserArr[t+1])) * (*getBeta(t+1, jdx)));
         }

         //scale beta_ti with same scale factor as a_ti
         *getBeta(t, idx) = (*getBeta(t, idx)) * (*getC(t));
      }
   }
}

void HMM::calcGammaDigamma(int* obserArr, int T)
{
   for (int t = 0; t < T-1; t++) {
      for (int idx = 0; idx < mN; idx++) {
         *getGamma(t, idx) = 0;
         for (int jdx = 0; jdx < mN; jdx++) {
            //No need to normalize since using scaled alpha and beta 
            *getDiGamma(t, idx, jdx) = (*getAlpha(t, idx)) * (*getA(idx, jdx)) * (*getB(jdx, obserArr[t+1])) * (*getBeta(t+1, jdx));
            *getGamma(t, idx) = (*getGamma(t, idx)) + (*getDiGamma(t, idx, jdx));
         }
      }
   }

   //special case for gamma_t-1(i)
   //No need to normalize since using scaled alpha and beta 
   for (int idx = 0; idx < mN; idx++) *getGamma(T-1, idx) = *getAlpha(T-1, idx);
  
}

void HMM::reEstimateModel(int* obserArr, int T)
{
   //re-estimate PI
   for (int idx = 0; idx < mN; idx++) *getPI(idx) = *getGamma(0, idx);

#ifndef USE_FIXED_DIGRAPH
   //re-estimate A
   for (int idx = 0; idx < mN; idx++) {
      for (int jdx = 0; jdx < mN; jdx++) {
         float numer = 0;
         float denom = 0;
         for (int t = 0; t < T-1; t++) {
            numer += *getDiGamma(t, idx, jdx);
            denom += *getGamma(t, idx);
         }
         if (numer == 0) *getA(idx, jdx) = 0;
         else *getA(idx, jdx) = numer / denom;
      }
   }
#endif

   //re-estimate B
   for (int idx = 0; idx < mN; idx++) {
      for (int jdx = 0; jdx < mM; jdx++) {
         float numer = 0;
         float denom = 0;
         for (int t = 0; t < T; t++) {
            if (obserArr[t] == jdx) numer += *getGamma(t, idx);
            denom += *getGamma(t, idx);
         }
         if (numer == 0) *getB(idx, jdx) = 0;
         else *getB(idx, jdx) = numer / denom;
      }
   }
}


float* HMM::getA(int i, int j)
{
#ifndef USE_FIXED_DIGRAPH
   return mA + (i*mN) + j;
#else
   return &DigraphAMat[i][j];
#endif
}
float* HMM::getB(int i, int j)
{
   return mB + (i*mM) + j;
}
float* HMM::getPI(int i)
{
   return mPI + i; 
}

float* HMM::getC(int t)
{
   return mC + t; 
}
float* HMM::getAlpha(int t, int i)
{
   return mAlpha + (t*mN) + i; 
}
float* HMM::getBeta(int t, int i)
{
   return mBeta + (t*mN) + i;
}
float* HMM::getGamma(int t, int i)
{
   return mGamma + (t*mN) + i;
}
float* HMM::getDiGamma(int t, int i, int j)
{
   return mDiGamma + (t*mN*mN) + (i*mN) + j;
}


//predict the simple shift key assume 
//HHM is trained with: A is fixed digraph matrix, N = M = 26
static int predictMapping(HMM* hmm) {
   //this is the group truth key to be compared
   //e.g., gtKey[0] = 4, then 'a'(0) maps to 'e'(4)
   static const int gtKey[26] = {4, 9, 21, 6, 25, 23, 13, 8, 1, 7, 15, 22, 18, 3, 17, 16, 0, 20, 12, 5, 2, 11, 14, 24, 10, 19};

   int cor = 0;
   for (int i = 0; i < 26; i++) {
      float maxP = 0.0;
      int maxJ = -1;
      for (int j = 0; j < 26; j++) {
         if (*hmm->getB(j, i) >= maxP) {
            maxP = *hmm->getB(j, i);
            maxJ = j;
         }
      }
      if (gtKey[maxJ] == i) cor++;
   }
   printf("cor = %d\n", cor);
   return cor;
}

#ifndef _NO_MAIN
int main(int argc, const char** argv) {
   if (argc != 6) {
      printf("Usage: %s <txt> <N> <T> <minIters> <epsilon>\n", argv[0]);
      return -1;
   }

   const int N = std::stoi(argv[2]);
   const int M = ObserSet.length();
   int T = std::stoi(argv[3]);
   const int minIters = std::stoi(argv[4]);
   const float epsilon = std::stof(argv[5]);
   int* obsers = (int*)malloc(T*sizeof(int));
   if (!obsers) {
      printf("no memory\n");
      return -2;
   }

   //prepare observation sequence from txt file
   printf("using txt file %s\n", argv[1]);
   std::ifstream is(argv[1], std::ifstream::in);
   char c;
   int i = 0;
   while (is.get(c)) {
      int idx = ObserSet.find(c);
      if (idx == std::string::npos) continue;
      obsers[i] = idx;
      i++;
      if (i >= T) break;
   }
   is.close();
   if (i < T) {
      printf("file %s has %d less than %d chars\n", argv[2], i, T);
      T = i;
   }

   //start training
   HMM* hmm = new HMM(N, M, minIters, epsilon);
   if (!hmm) {
      printf("no memory\n");
      return -3;
   }

   printf("start training HMM for seq N = %d, M = %d, minIters = %d, eps = %.6f, T = %d\n", N, M, minIters, epsilon, T);
   hmm->fit(obsers, T);

#ifdef USE_FIXED_DIGRAPH
   int cor = predictMapping(hmm);
#endif

   //clean up and exit
   delete hmm;
   free(obsers);
   return 0;
}
#endif



