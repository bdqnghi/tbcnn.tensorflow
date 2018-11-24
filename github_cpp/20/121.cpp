/*
 *
 * HMM.cpp
 *
 *  Created on: Feb 18, 2012
 *      Author: alberto
 */

#include "HMM.h"

HMM::HMM(int hiddenStates, int alphabet) {
	this->hiddenStates = hiddenStates;
	this->alphabet = alphabet;

	// O and Q are mantained to be consistent with MATLAB code
	int O = alphabet; // alphabet
	int Q = hiddenStates; // hidden states
	this->prior = normalise(randu<mat>(Q,1));
	this->transmat = mk_stochastic(randu<mat>(Q,Q));
	this->obsmat = mk_stochastic(randu<mat>(Q,O));

	this->name = "an hidden markov model";
}

HMM::HMM(int hiddenStates, int alphabet, mat prior, mat transmat, mat obsmat) {
	this->hiddenStates = hiddenStates;
	this->alphabet = alphabet;
	this->prior = prior;
	this->transmat = transmat;
	this->obsmat = obsmat;

	this->name = "an hidden markov model";
}

HMM::~HMM() {
	// TODO Auto-generated destructor stub
}

//------------------------------------------------------------- public

vector<double> HMM::train(field<rowvec> data, int max_iter) {
	//cout << "HMM::train. data:" << data << endl;
	this->_training_data = data;
	vector<double> LL = dhmm_em(data, max_iter);
	this->LL = LL;
	return LL;
}

double HMM::evaluate(field<rowvec> data) {
	double loglik1 = dhmm_logprob(data);
	return loglik1;
}

//------------------------------------------------------------- MATLAB stuff

bool HMM::em_converged(double loglik, double previous_loglik, double threshold) {

	/*
	 * Has EM converged?
	 *
	 * We have converged if the slope of the log-likelihood function falls below 'threshold',
	 * i.e., |f(t) - f(t-1)| / avg < threshold,
	 * where avg = (|f(t)| + |f(t-1)|)/2 and f(t) is log lik at iteration t.
	 * 'threshold' defaults to 1e-4.
	 *
	 * This stopping criterion is from Numerical Recipes in C p423
	 *
	 * If we are doing MAP estimation (using priors), the likelihood can decrase,
	 * even though the mode of the posterior is increasing.
	 *
	 */

	double converged = 0;
	double decrease = 0;

	if (loglik - previous_loglik < -1e-3) { // allow for a little imprecision
		cout<<"******likelihood decreased from "<<previous_loglik<<" to "<<loglik<<endl;
		decrease = 1;
		converged = 0;
		return converged;
	}
	double delta_loglik = abs(loglik - previous_loglik);
	double avg_loglik = (abs(loglik) + abs(previous_loglik) + DBL_EPSILON)/2;
	if ((delta_loglik / avg_loglik) < threshold)
		converged = 1;
	return converged;
}

void HMM::_fwdback(mat init_state_distrib, mat _transmat, mat obslik,
		mat &alpha, mat &beta, mat& gamma, double &loglik, mat &xi_summed,
		cube &gamma2, cube &obslik2,
		bool fwd_only, bool compute_gamma2) {

	/*
	 * Compute the posterior probs. in an HMM using the forwards backwards algo.
	 *
	 * Notation:
	 *  Y(t) = observation, Q(t) = hidden state, M(t) = mixture variable (for MOG outputs)
	 *  A(t) = discrete input (action) (for POMDP models)
	 *
	 * INPUT:
	 *  init_state_distrib(i) = Pr(Q(1) = i)
	 *  transmat(i,j) = Pr(Q(t) = j | Q(t-1)=i)
	 *   or transmat{a}(i,j) = Pr(Q(t) = j | Q(t-1)=i, A(t-1)=a) if there are discrete inputs
	 *  obslik(i,t) = Pr(Y(t)| Q(t)=i)
	 *
	 */

	bool scaled = true;
	bool maximize = false;
	bool compute_xi = true;

	int Q = obslik.n_rows;
	int T = obslik.n_cols;

	mat mixmat;
	mat act;	// qui act è tutti zero, altrimenti potrebbe essere un input, TODO aggiungere &act negli input
	mat scale;

	if (obslik2.is_empty())
		compute_gamma2 = false;

	act = zeros(1,T);			// TODO this could be a colvec
	scale = ones(1,T);
	field<mat> transmat(1,1);
	transmat(0,0) = _transmat;

	// scale(t) = Pr(O(t) | O(1:t-1)) = gamma21/c(t) as defined by Rabiner (1989).
	// Hence prod_t scale(t) = Pr(O(1)) Pr(O(2)|O(1)) Pr(O(3) | O(1:2)) ... = Pr(O(1), ... ,O(T))
	// or log P = sum_t log scale(t).
	// Rabiner suggests multiplying beta(t) by scale(t), but we can instead
	// normalise beta(t) - the constants will cancel when we compute gamma.

	if (compute_xi)
		xi_summed = zeros(Q,Q);
	//else
	// xi_summed = [];

	//%%%%%%%%% Forwards %%%%%%%%%%
	//cout << "fwdback > Forwards" << endl;

	int t = 0;
	alpha.col(0) = vectorize(init_state_distrib) % obslik.col(t);
	if (scaled){
		std::pair<mat,double> _tmp = normaliseC(alpha.col(t));
		alpha.col(t) = _tmp.first;
		scale(t) = _tmp.second;
	}

	for(int t=1; t<T; t++) {
		mat trans;
		mat m;

		trans = transmat(act(t-1));

		if (maximize){
			//m = max_mult(trans.t(), alpha.col(t-1)); // TODO max_mult
		} else {
			m = trans.t() * alpha.col(t-1);
		}

		alpha.col(t) = vectorize(m) % obslik.col(t);

		if (scaled) {
			std::pair<mat,double> _tmp = normaliseC(alpha.col(t));
			alpha.col(t) = _tmp.first;
			scale(t) = _tmp.second;
		}

		if (compute_xi && fwd_only) {// useful for online EM
			xi_summed = xi_summed + normalise((alpha.col(t-1) * obslik.col(t).t()) % trans);
		}
	}

	if (scaled) {
		uvec _s = find(scale);  	// se c'è almeno uno zero
									// portando a logaritmo c'è almeno un infinito
									// quindi somma tutto a infinito
		if ( _s.is_empty() ) {
			loglik = -std::numeric_limits<double>::max();
		} else {
			loglik = sum(sum(log(scale))); // nested arma::sum because sum(mat X) return a rowvec
		}
	} else {
		loglik = log(sum(alpha.col(T)));
	}

	if (fwd_only) {
		gamma = alpha;
		return;
	}

	//%%%%%%%%% Backwards %%%%%%%%%%
	//cout << "fwdback > Backwards" << endl;

	int M;
	mat trans;
	mat denom;

	beta = zeros(Q,T);
	if (compute_gamma2) {
		M = mixmat.n_cols;
		gamma2 = zeros(Q,M,T);
	} else {
		//gamma2 = []
	}

	beta.col(T-1) = ones(Q,1);

	gamma.col(T-1) = normalise(alpha.col(T-1) % beta.col(T-1));
	t=T-1;

	if (compute_gamma2) {
		denom = obslik.col(t) + (obslik.col(t)==0); // replace 0s with 1s before dividing
		gamma2.slice(t) = obslik2.slice(t) % mixmat % repmat(gamma.col(t), 1, M) % repmat(denom, 1, M);
	}

	for (int t=T-2; t>=0; t--) { // T-2 because there are some calls to t+1
								 // and col(T) will generate the error Mat::col(): out of bounds
					             // so we must assure the limit of col(T-1)
		mat b = beta.col(t+1) % obslik.col(t+1);
		trans = transmat(act(t));
		if (maximize){
			mat B = repmat(vectorize(b).t(), Q, 1);
			beta.col(t) = max(trans % B, 1);
		} else
			beta.col(t) = trans * b;

		if (scaled)
			beta.col(t) = normalise( beta.col(t) );

		gamma.col(t) = normalise(alpha.col(t) % beta.col(t));

		if (compute_xi){
			xi_summed = xi_summed + normalise((trans % (alpha.col(t) * b.t())));
		}

		if (compute_gamma2){
			denom = obslik.col(t) + (obslik(t)==0); // replace 0s with 1s before dividing
			gamma2.slice(t) = obslik2.slice(t) % mixmat % repmat(gamma.col(t), 1, M) % repmat(denom, 1, M);
		}
	}
}

void HMM::fwd(mat init_state_distrib, mat _transmat, mat obslik,
		mat &alpha, mat &beta, mat& gamma, double &loglik, mat &xi_summed, cube &gamma2, cube &obslik2) {

	_fwdback(init_state_distrib, _transmat, obslik,
			alpha, beta, gamma, loglik, xi_summed, gamma2, obslik2,
			true, false);
}

void HMM::fwdback(mat init_state_distrib, mat _transmat, mat obslik,
		mat& gamma, double &loglik, mat &xi_summed) {
	/*
	 * caller of forward-backwards algorithm without:
	 *  - compute_gamma2
	 *  - returning of alpha and beta
	 */

	cube gamma2;
	cube obslik2;

	int Q = obslik.n_rows;
	int N = obslik.n_cols;

	mat alpha = zeros(Q,N);
	mat beta; 		// if fwd only beta is null, but in bwd is zeros(Q,T)

	_fwdback(init_state_distrib, _transmat, obslik,
			alpha, beta, gamma, loglik, xi_summed, gamma2, obslik2,
			false, false);

}

void HMM::compute_ess_dhmm(mat startprob, mat transmat, mat obsmat, field<rowvec> data,
		double &loglik, mat &exp_num_trans, mat &exp_num_visits1, mat &exp_num_emit, mat &exp_num_visitsT) {
	/*
	 * Compute the Expected Sufficient Statistics for an HMM with discrete outputs
	 *
	 * INPUTS:
	 *  startprob(i)
	 *  transmat(i,j)
	 *  obsmat(i,o)
	 *  data{seq}(t)
	 *  dirichlet - weighting term for uniform dirichlet prior on expected emissions
	 *
	 * OUTPUTS:
	 *  exp_num_trans(i,j) = sum_l sum_{t=2}^T Pr(X(t-1) = i, X(t) = j| Obs(l))
	 *  exp_num_visits1(i) = sum_l Pr(X(1)=i | Obs(l))
	 *  exp_num_visitsT(i) = sum_l Pr(X(T)=i | Obs(l))
	 *  exp_num_emit(i,o) = sum_l sum_{t=1}^T Pr(X(t) = i, O(t)=o| Obs(l))
	 *  where Obs(l) = O_1 .. O_T for sequence l.
	 *
	 *
	 */
	//cout << "compute_ess_dhmm" << endl;

	int numex = data.n_elem;
	int O = obsmat.n_cols;

	for (int ex=0; ex<numex; ex++) {

		// initialization of EM
		rowvec obs = data(ex,0);
		if (obs.n_elem == 0) continue;

		mat obslik = multinomial_prob(obs, obsmat);

		int T = obs.n_elem;
		int Q = obslik.n_rows;
		int N = obslik.n_cols;
		double current_ll = 0;

		mat gamma = zeros(Q,N);
		mat xi_summed; 	// if compute_xi is zeros(Q,Q), else is null

		fwdback(startprob, transmat, obslik,
				gamma, current_ll, xi_summed);

		loglik = loglik +  current_ll;
		exp_num_trans = exp_num_trans + xi_summed;
		exp_num_visits1 = exp_num_visits1 + gamma.col(0);
		exp_num_visitsT = exp_num_visitsT + gamma.col(T-1);

		if (T < O) {
			for(int t=1; t<T; t++) {
				int o = obs[t];
				exp_num_emit.col(o-1) = exp_num_emit.col(o-1) + gamma.col(t);
			}
		} else {
			for(int o=0; o<=O; o++) {
				uvec ndx = find(obs==o);
				if (!ndx.is_empty()) {
					mat sumgamma = sum(get_cols(gamma,ndx), 1);
					exp_num_emit.col(o-1) = exp_num_emit.col(o-1) + sumgamma;
				}
			}
		}
	}
}

vector<double> HMM::dhmm_em(field<rowvec> data, int max_iter) {
	/*
	 * Find the ML/MAP parameters of an HMM with discrete outputs using EM.
	 *
	 * Notation: Q(t) = hidden state, Y(t) = observation
	 */
	//cout << "dhmm_em"<<endl;

	double previous_loglik = - std::numeric_limits<double>::max();
	double thresh =  1e-4;
	double converged = 0;
	int num_iter = 1;
	int obs_prior_weight = 0; 	// weighting term for uniform dirichlet prior on expected emissions

	vector<double> LL;

	while ((num_iter <= max_iter) && !converged)  {

		double loglik = 0;
		int S = obsmat.n_rows;
		int O = obsmat.n_cols;

		mat exp_num_trans = zeros(S,S);		// all values initialized here for allocation issue (?) TODO: to be tested
		mat exp_num_visits1 = zeros(S,1);
		mat exp_num_visitsT = zeros(S,1);
		mat exp_num_emit = obs_prior_weight*ones(S,O);	// obs_prior_weight is dirichlet in Kevin Murphy's code

		// E step
		compute_ess_dhmm(prior, transmat, obsmat, data,
				loglik, exp_num_trans, exp_num_visits1, exp_num_emit, exp_num_visitsT);

		// M step
		prior = normalise(exp_num_visits1);
		if (!exp_num_trans.is_empty())
			transmat = mk_stochastic(exp_num_trans);
		obsmat = mk_stochastic(exp_num_emit);

		std::cout << "iteration " << num_iter << ", loglik = " << loglik << endl;

		num_iter =  num_iter + 1;
		converged = em_converged(loglik, previous_loglik, thresh);
		previous_loglik = loglik;
		LL.push_back(loglik);
	}
	return LL;
}

double HMM::dhmm_logprob(field<rowvec> data) {
	/*
	 *  Compute the log-likelihood of a dataset using a discrete HMM
	 */

	int ncases = data.n_elem;
	double loglik = 0;

	for (int m=0; m<ncases; m++) {//m=1:ncases

		mat obslik = multinomial_prob(data(m,0), obsmat);

		int T = data.n_elem;
		int Q = obslik.n_rows;
		int N = obslik.n_cols;
		double ll = 0;

		mat alpha = zeros(Q,N);
		mat gamma = zeros(Q,N);
		mat beta; 		// if fwd only beta is null, but in bwd is zeros(Q,T)
		mat xi_summed; 	// if compute_xi is zeros(Q,Q), else is null

		cube gamma2;
		cube obslik2;

		fwd(prior, transmat, obslik,
			alpha, beta, gamma, ll, xi_summed, gamma2, obslik2);

	  if (ll == -std::numeric_limits<double>::max()) {
		  //cout << "dhmm_logprob loglik is -inf!!" << endl;
	  }

	  loglik = loglik + ll;
	}

	return loglik;
}

//------------------------------------------------------------- getter && setter

vector<double> HMM::getLL() const {
	return this->LL;
}

mat HMM::getObsmat() const
{
    return obsmat;
}

mat HMM::getPrior() const
{
    return prior;
}

mat HMM::getTransmat() const
{
    return transmat;
}

void HMM::setObsmat(mat obsmat)
{
    this->obsmat = obsmat;
}

void HMM::setPrior(mat prior)
{
    this->prior = prior;
}

void HMM::setTransmat(mat transmat)
{
    this->transmat = transmat;
}


