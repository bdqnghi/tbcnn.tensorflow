/*
@abstract(code for the tutorial on hidden Markov models )
@author(Nikolai Shokhirev <nikolai@shokhirev.com> <nikolai@u.arizona.edu>
        http://www.shokhirev.com/nikolai.html
        http://www.u.arizona.edu/~nikolai/
        http://www.chem.arizona.edu/~shokhirn/nikolai.html )
@created(2006.02.02)
�Nikolai V. Shokhirev, 2003-2006
 2006.02.24 - added PosteriorDecodingIdxs }
*/
//---------------------------------------------------------------------------
#pragma hdrstop

#include "HMM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

HMM:: HMM()
{
  N = 0;
  M = 0;
  Tmax = 0;
}

HMM::HMM(FArr2D& TransProb, FArr2D& ObsProb, FArr1D& InitProb)
{
  N = TransProb.D1();
  M = ObsProb.D2();
/*
  FArr2D  A(N,N);
  FArr2D  B(N,M);
  FArr1D  P0(N);
*/
  pA = new FArr2D(TransProb);
  pB = new FArr2D(ObsProb);
  pP0 = new FArr1D(InitProb);

  A = *pA;
  B = *pB;
  P0 = *pP0;
}

HMM:: ~HMM()
{
  delete pA;
  delete pB;
  delete pP0;
  delete pbeta;
  delete palpha;
}

// Forward algorithm
real HMM::GetProbabilityF(IArr1D& ObsIdxs)
{
  real sum = 0.0;
  Tmax = ObsIdxs.D1();

  palpha = new FArr2D(Tmax,N);
  alpha = *palpha;
  // Initialization
  int t = 1;
  for (int i = 1; i <= N; i++)
    alpha(t,i) = P0(i)*B(i,ObsIdxs(t));

  // Recursion
  for (t = 1; t < Tmax; t++)
  {
    for (int j = 1; j <= N; j++)
    {
      sum = 0.0;
      for (int i = 1; i <= N; i++)
        sum += alpha(t,i)*A(i,j);

      alpha(t+1,j) = sum*B(j,ObsIdxs(t+1));
    };
  }
  // Termination
  t = Tmax;
  sum = 0.0;
  for (int i = 1; i <= N; i++)
    sum += alpha(t,i);

  return sum;
}

// Backward algorithm
real HMM::GetProbabilityB(IArr1D& ObsIdxs)
{
  real sum = 0.0;
  Tmax = ObsIdxs.D1();
  pbeta = new FArr2D(Tmax,N);
  beta = *pbeta;

  // Initialization
  int t = Tmax;
  for (int i = 1; i <= N; i++)
    beta(t,i) = 1.0;

  // Recursion
  for (t = Tmax-1; t >=1; t--)
  {
    for (int i = 1; i <= N; i++)
    {
      sum = 0.0;
      for (int j = 1; j <= N; j++)
        sum += A(i,j)*B(j,ObsIdxs(t+1))*beta(t+1,j);

      beta(t,i) = sum;
    };
  }

  // Termination
  t = 1;
  sum = 0.0;
  for (int i = 1; i <= N; i++)
    sum += P0(i)*B(i,ObsIdxs(t))*beta(t,i);

  return sum;
}

// Viterbi algorithm
IArr1D HMM::ViterbiStateIdxs(IArr1D& ObsIdxs)
{
  real p, q;
  int t, k, i;
  IArr1D StateIdxs(Tmax);
  FArr2D delta(Tmax, N);
  IArr2D psi(Tmax, N);

  // Initialization
  t = 1;
  for (int i = 1; i <= N; i++)
  {
    delta(t,i) = P0(i)*B(i,ObsIdxs(t));
    psi(t,i) = 0; // Outside limits - not used
  };

  // Recursion
  for (t = 2; t <= Tmax; t++)
  {
    for (int j = 1; j <= N; j++)
    {
      p = 0.0;
      k = 0; // Outside limits, must be redefined below
      for (int i = 1; i <= N; i++)
      {
        q = delta(t-1,i)*A(i,j);
        if ( q > p )
        {
          p = q;
          k = i;
        };
      };
      delta(t,j) = p*B(j,ObsIdxs(t));
      psi(t,j) = k;
    };
  };

  // Termination
  t = Tmax;
  p = 0.0;
  k = 0; // Outside limits, must be redefined below
  for (int i = 1; i <= N; i++)
  {
    q = delta(t,i);
    if ( q > p )
    {
      p = q;
      k = i;
    };
  };
  StateIdxs(t) = k;  // q* in Rabiner's paper

  // Path (state sequence) backtracking
  for (t = Tmax-1; t >=1; t--)
  {
    StateIdxs(t) = psi(t+1, StateIdxs(t+1));
  };

  return StateIdxs;
}

// Posterior Decoding
IArr1D HMM::PosteriorDecodingIdxs(IArr1D& ObsIdxs)
{
  real p, q;
  int t, k;
  IArr1D StateIdxs(Tmax);

  // calculate alpha
//  real PF = GetProbabilityF(ObsIdxs);
  // calculate beta
//  real PB = GetProbabilityB(ObsIdxs);


  for (t = 1; t <= Tmax; t++)
  {
    p = 0.0;
    k = 1; // Outside limits, must be redefined below
    for (int i = 1; i <= N; i++)
    {
      q = alpha(t,i)*beta(t,i);
      if ( q > p )
      {
        p = q;
        k = i;
      };
    };
    StateIdxs(t) = k;
  };

  return StateIdxs;
}
