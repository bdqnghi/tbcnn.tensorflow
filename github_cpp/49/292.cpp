// [[Rcpp::depends(RcppArmadillo)]]
#include <iostream>
//include <math.h>
#include <RcppArmadillo.h>
using namespace std;
using namespace Rcpp;
using namespace arma;

/* Prepare */
/* Random number generation from a multivariate normal */
mat mvrnormArma(int n, vec mu, mat Sigma) {
  int ncols = Sigma.n_cols;
  mat Y = randn(n, ncols);
  return repmat(mu, 1, n).t() + Y * arma::chol(Sigma);
}

/* Gibbs sampler for the homoskedastic linear regression model */
// [[Rcpp::export]]
List lm_gibbs(vec y, mat X, vec b0, mat B0, double a0, double s0,
              double sigma_start, int burn, int iter, int thin = 1) {
  /* Prepare */
  int n = X.n_rows;
  int k = X.n_cols;

  /* Parameters of posterior distributions */
  double sigma2 = sigma_start;
  double a1 = a0 + n;
  
  /* Matrices to store sampled values */
  mat beta_mat = zeros<mat>(iter/thin, k);
  vec sigma_vec = zeros<vec>(iter/thin);

  /* Burn-in */
  for (int i = 1; i <= burn; i++){
    /* Update beta */
    mat B1 = inv(B0.i() + ((double)1 / sigma2) * X.t() * X);
    vec b1 = B1 * (B0.i() * b0 + ((double)1 / sigma2) * X.t() * y);
    mat beta = mvrnormArma(1, b1, B1).t();
    /* Update sigma^2 */
    double s1 = as_scalar(trans(y - X * beta) * (y - X * beta)) + s0;
    sigma2 = (double)1/R::rgamma(a1/(double)2, (double)2/s1);
  }
  
  cout << "Burn-in period has fninished." << "\n";
  
  /* Main iteration loop */
  for (int i = 1; i <= iter; i++){
    /* Update beta */
    mat B1 = inv(B0.i() + ((double)1 / sigma2) * X.t() * X);
    vec b1 = B1 * (B0.i() * b0 + ((double)1 / sigma2) * X.t() * y);
    mat beta = mvrnormArma(1, b1, B1).t();
    /* Update sigma^2 */
    double s1 = as_scalar(trans(y - X * beta) * (y - X * beta)) + s0;
    sigma2 = (double)1/R::rgamma(a1/(double)2, (double)2/s1);
    /* store sampled values */
    if (i % thin == 0){
      beta_mat.row((i/thin) - 1) = beta.t();
      sigma_vec((i/thin) - 1) = sigma2;
    }
  }
  
  cout << "Main iteration loop has fninished." << "\n";
  
  /* Return values */
  return List::create(Named("beta") = beta_mat,
                      Named("sigma2") = sigma_vec);
}

