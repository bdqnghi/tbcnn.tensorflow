//LogisticRegression.cpp

#include "LogisticRegression.h"
#include "ComboGenerator.h"
#include "Helpers.h"
namespace Methods{
///
/// Constructor
///
LogisticRegression::LogisticRegression(){
  set = NULL;
  initialize();
}


///
/// Alternative constructor
///
LogisticRegression::LogisticRegression(DataSet* ds){
  set = ds;
  initialize();
}

///
/// Initialize starting variables
///
void LogisticRegression::initialize(){
  fullInteraction = true;
  modelSize = 0;
  maxLocusValue = 2;
  missingValue = maxLocusValue+1;
  LociComboLimit = 10;
  LociComboMin = 1;
  maxIterations = 20;
  modType = Additive;
  defaultComboInterval = 10000;
  includeInteractions = false;
  coeff_intercept = 0.0;
  missingCoValue = -99999;

  ModelTypeMap["DOMINANT"] = Dominant;
  ModelTypeMap["RECESSIVE"] = Recessive;
  ModelTypeMap["ADDITIVE"] = Additive;

  PiD2 = 3.141592653589793 / 2;
  set_model();

  initialize_interactions();
}


///
/// Generates and stores interaction lists for producing interaction
/// terms when doing multi-locus models
///
void LogisticRegression::initialize_interactions(){
  vector<vector<unsigned int> > blank_vector;

  interaction_lists.clear();

  // indexes 0 and 1 contain empty vectors as placeholders
  // so that index of the interaction list will match
  // number of loci in the model
  interaction_lists.push_back(blank_vector);
  interaction_lists.push_back(blank_vector);

  unsigned int comboIndex;
  for(unsigned int curr_num=2; curr_num <= LociComboLimit; curr_num++){
    interaction_lists.push_back(blank_vector);

    ComboGenerator generator;
    generator.ComboEnds(2, curr_num);
    generator.SetLoci(curr_num);
    generator.SetComboInterval(defaultComboInterval);
    bool done=true;

    do{
      done = generator.GenerateCombinations();
      for(comboIndex=0; comboIndex < generator.ComboList.size(); comboIndex++){
        interaction_lists.at(curr_num).push_back(generator.ComboList.at(comboIndex));
      }
    }while(!done);

  }
}


///
/// Runs logistic regression on dataset referenced in this method <br>
/// @param loci
/// @return none
///
void LogisticRegression::calculate(vector<unsigned int>& loci){
  vector<unsigned int> traits, covars;
  calculate(loci,covars,traits);

  // when model is too large for current interaction list
  // update interactions
//   if(loci.size() > LociComboLimit){
//     LociComboLimit = loci.size();
//     initialize_interactions();
//   }
// 
//   vector<int> includedCells = includedIndexes.at(loci.size());
//   vector<unsigned int> converted_loci = convert_loc_order(loci);
// 
//   summarize_data(loci);
//   // assume loci are in marker_map order so need to alter to order contained
//   // in samples
// 
//   // run routine that calculates LR values
//   calculateLR(summary_data, true, includedCells);
}


///
/// Reset data and set markers vector pointer
/// @param ds DataSet pointer
///
void LogisticRegression::resetDataSet(DataSet* ds){
  set = ds;
  markers = set->get_markers();
  missingValue = set->get_missing_value();
  missingCoValue = set->get_missing_covalue();

  int numGenosPerLocus = set->get_max_locus()+1;
  missingValue = numGenosPerLocus;
  if(set->missing_data_present())
    numGenosPerLocus++;

  indexConverter.set_genos_per_locus(numGenosPerLocus);
  indexConverter.set_included_indexes(LociComboMin, LociComboLimit,
    !set->missing_data_present(), missingValue);
  includedIndexes = indexConverter.get_included_indexes();

}


///
/// Runs logistic regression on dataset passed <br>
/// @param resultList ResultSet that may contain results from other filters
/// and will contain results of this sequential replication analysis
/// @param dataset DataSet to be analyzed
/// @return none
///
void LogisticRegression::calculate(vector<unsigned int>& loci, DataSet* dataset){
  resetDataSet(dataset);
  calculate(loci);
}


void LogisticRegression::calculateLR(vector<vector<double> >& data,
		bool summary_data, vector<int>& includedCells) {

	unsigned int nRows = includedCells.size();
	// number of coefficients is equal to the main effects + the interactions
	unsigned int nColumns = data.at(0).size() - 2;
	if (!summary_data)
		nColumns++;

	unsigned int nP = nColumns + 1;
	unsigned int nP1 = nP + 1;
	unsigned int sY0 = 0;
	unsigned int sY1 = 0;
	unsigned int sC = 0;
	double x;
	double v, xij, s, q;

	unsigned int unaffIndex = data.at(0).size() - 2;
	unsigned int affIndex = unaffIndex + 1;

	vector<double> X(nRows * (nColumns + 1), 0);
	vector<unsigned int> Y0(nRows, 0);
	vector<unsigned int> Y1(nRows, 0);
	vector<double> xM(nColumns + 1, 0.0);
	vector<double> xSD(nColumns + 1, 0.0);
	vector<double> Par(nP);
	coefficients.clear();
	standard_errors.clear();
	coefficients.resize(nP - 1);
	coeff_pvalues.resize(nP - 1);
	standard_errors.resize(nP - 1);

	vector<double> SEP(nP);
	vector<double> Arr(nP * nP1);

	unsigned int i, j, k;

	// This loop stores the original values in X and adds values into
	// xM and xSD for mean and standard deviation calculations
	for (i = 0; i < nRows; i++) {
		X.at(ix(i, 0, nColumns + 1)) = 1;
		// store predictor values
		for (j = 1; j <= nColumns; j++) {
			X.at(ix(i, j, nColumns + 1)) = data.at(includedCells.at(i)).at(j
					- 1);
		}

		// status handled differently if data is summary
		if (summary_data) {
			Y0.at(i) = (unsigned int) (data.at(includedCells.at(i)).at(
					unaffIndex));
			sY0 += Y0.at(i);
			Y1.at(i)
					= (unsigned int) (data.at(includedCells.at(i)).at(affIndex));
			sY1 += Y1.at(i);
		} else { // not summary
			if (data.at(includedCells.at(i)).back() == 0) {
				Y0.at(i) = 1;
				sY0++;
			} else {
				Y1.at(i) = 1;
				sY1++;
			}
		}

		sC += Y0.at(i) + Y1.at(i);

		for (j = 1; j <= nColumns; j++) {
			x = X.at(ix(i, j, nColumns + 1));
			xM.at(j) += (Y0.at(i) + Y1.at(i)) * x;
			xSD.at(j) += (Y0.at(i) + Y1.at(i)) * x * x;
		}
	}

	// calculate mean and standard deviation
	for (j = 1; j <= nColumns; j++) {
		xM.at(j) = xM.at(j) / sC;
		xSD.at(j) = xSD.at(j) / sC;
		xSD.at(j) = sqrt(fabs(xSD.at(j) - xM.at(j) * xM.at(j)));
	}

	xM.at(0) = 0;
	xSD.at(0) = 1;

	// adjusts X values using the mean and standard deviation values
	for (i = 0; i < nRows; i++) {
		for (j = 1; j <= nColumns; j++) {
			X.at(ix(i, j, nColumns + 1)) = (X.at(ix(i, j, nColumns + 1))
					- xM.at(j)) / xSD.at(j);
		}
	}

	Par.at(0) = log(double(sY1) / sY0); // use natural log of the ratio
	for (j = 1; j <= nColumns; j++) { // zero out all the others
		Par.at(j) = 0;
	}

	double LnV = 0, Ln1mV = 0, LLn = 0;
	double LLp = 2e+10; // stores previous value of LL to check for convergence
	double LL = 1e+10;
	unsigned int numIterations = 0;

	while (fabs(LLp - LL) > 0.0000001) {
		if (++numIterations > maxIterations) {
			break;
		}

		LLp = LL;
		LL = 0;

		// zero out Arr for this iteration
		for (j = 0; j <= nColumns; j++) {
			for (k = j; k <= nColumns + 1; k++) {
				Arr.at(ix(j, k, nColumns + 2)) = 0;
			}
		}

		// add to LL for each row
		for (i = 0; i < nRows; i++) {
			v = Par.at(0); // for this ind start with Par.at(0) value
			for (j = 1; j <= nColumns; j++) {
				v = v + Par.at(j) * X.at(ix(i, j, nColumns + 1)); // add the value of Par for column and the value at that column
			}
			if (v > 15) {
				LnV = -exp(-v);
				Ln1mV = -v;
				q = exp(-v);
				v = exp(LnV);
			} else {
				if (v < -15) {
					LnV = v;
					Ln1mV = -exp(v);
					q = exp(v);
					v = exp(LnV);
				} else {
					v = 1 / (1 + exp(-v));
					LnV = log(v);
					Ln1mV = log(1 - v);
					q = v * (1 - v);
				}
			}
			// calculate LL for this ind and add to running total
			LL = LL - 2 * Y1.at(i) * LnV - 2 * Y0.at(i) * Ln1mV;
			for (j = 0; j <= nColumns; j++) {
				xij = X.at(ix(i, j, nColumns + 1));

				Arr.at(ix(j, nColumns + 1, nColumns + 2)) = Arr.at(ix(j,
						nColumns + 1, nColumns + 2)) + xij * (Y1.at(i)
						* (1 - v) + Y0.at(i) * (-v));
				for (k = j; k <= nColumns; k++) {
					Arr.at(ix(j, k, nColumns + 2)) = Arr.at(ix(j, k, nColumns
							+ 2)) + xij * X.at(ix(i, k, nColumns + 1)) * q
							* (Y0.at(i) + Y1.at(i));
				}
			}
		}

		// when this is the first iteration, set LLn (null model) to be the current value of LL
		if (LLp == 1e+10) {
			LLn = LL;
		}

		for (j = 1; j <= nColumns; j++) {
			for (k = 0; k < j; k++) {
				Arr.at(ix(j, k, nColumns + 2)) = Arr.at(ix(k, j, nColumns + 2));
			}
		}

		for (i = 0; i <= nColumns; i++) {
			s = Arr.at(ix(i, i, nColumns + 2));
			Arr.at(ix(i, i, nColumns + 2)) = 1;
			for (k = 0; k <= nColumns + 1; k++) {
				Arr.at(ix(i, k, nColumns + 2)) = Arr.at(ix(i, k, nColumns + 2))
						/ s;
			}
			for (j = 0; j <= nColumns; j++) {
				if (i != j) {
					s = Arr.at(ix(j, i, nColumns + 2));
					Arr.at(ix(j, i, nColumns + 2)) = 0;
					for (k = 0; k <= nColumns + 1; k++) {
						Arr.at(ix(j, k, nColumns + 2)) = Arr.at(ix(j, k,
								nColumns + 2)) - s * Arr.at(ix(i, k, nColumns
								+ 2));
					}
				}
			}
		}
		for (j = 0; j <= nColumns; j++) {
			Par.at(j) = Par.at(j) + Arr.at(ix(j, nColumns + 1, nColumns + 2));
		}
	} // complete iteration

	// calculate p values for the coefficients
	// interaction coefficient for all loci is the last one
	for (j = 1; j <= nColumns; j++) {
		Par.at(j) = Par.at(j) / xSD.at(j);
		Par.at(0) = Par.at(0) - Par.at(j) * xM.at(j);
	}

	if (isnan(LL)) {
		overallPvalue = coeffPvalue = 1.0;
		LLR = 0.0;
	} else {
		// calculate coefficient p value
		for (j = 1; j <= nColumns; j++) {
			SEP.at(j) = sqrt(Arr.at(ix(j, j, nP + 1))) / xSD.at(j);
		}
		j = nColumns;
		coeffPvalue = norm(fabs(Par.at(j) / SEP.at(j)));
		// calculate overall p value
		overallPvalue = ChiSq(fabs(LLn - LL), nColumns);

		coeff_intercept = Par.at(0);
		// adjust coefficients so that the zero index is now first coefficient
		for (j = 1; j <= nColumns; j++) {
			coefficients.at(j - 1) = Par.at(j);
			standard_errors.at(j - 1) = SEP.at(j);
			coeff_pvalues.at(j - 1) = norm(fabs(Par.at(j) / SEP.at(j)));
		}

		// calculate pseudo r-squared
		// http://statistics.ats.ucla.edu/stat/mult_pkg/faq/general/Psuedo_RSquareds.htm
		// using McFadden's method from page
		pseudo_r2 = 1 - LL / LLn;

		// calculate log-likelihood
		LLR = LLn - LL;
	}

}



///
/// Returns p value based on chi square scored passed and
/// degrees of freedom
/// @param x
/// @param n
/// @returns p value
///
double LogisticRegression::ChiSq(double x, unsigned int n) {

  if(x > 1000 || n>1000){
    double q = norm((pow(x/n,1/3)+2/(9*n)-1)/sqrt(2/(9*n)))/2;
    if(isnan(q)){
      return 0.0;
    }
    if(x>n){
      return q;
    }
    else{
      return 1-q;
    }
  }

  double p = exp(-0.5*x);
  if((n%2)==1) {
    p=p*sqrt(2*x/3.141592653589793);
  }
  unsigned int k=n;
  while(k>=2){
     p=p*x/k;
     k=k-2;
  }
  double t = p;
  unsigned int a=n;
  while(t>1e-15*p){
    a=a+2;
    t=t*x/a;
    p=p+t;
  }
  return 1-p;
}

///
/// Returns encoding for a genotype based on the model set.
/// @param geno Genotype value being checked
/// @param referent_allele Index of the allele that is the referent for the marker
/// @return recoded value for the genotype
///
int LogisticRegression::get_geno_conversion(int geno, int referent_allele){
	return geno_convert.at(referent_allele).at(geno);
}


///
/// Sets values to use for each genotype based on model selected <br>
/// Only works for SNPs currently.
///
void LogisticRegression::set_model(){
  // set up 2-D array
  geno_convert.assign(2, vector<unsigned int>(4,0));

  switch(modType){
    case Dominant:
      geno_convert.at(0).at(0) = 1;
      geno_convert.at(0).at(1) = 1;
      geno_convert.at(0).at(3) = 2;
      geno_convert.at(1).at(1) = 1;
      geno_convert.at(1).at(2) = 1;
      geno_convert.at(1).at(3) = 2;
      maxLocusValue = 1;
      break;
    case Recessive:
      geno_convert.at(0).at(0) = 1;
      geno_convert.at(0).at(3) = 2;
      geno_convert.at(1).at(2) = 1;
      geno_convert.at(1).at(3) = 2;
      maxLocusValue = 1;
      break;
    case Additive:
      geno_convert.at(0).at(1) = 1;
      geno_convert.at(0).at(0) = 2;
      geno_convert.at(0).at(3) = 3;
      geno_convert.at(1).at(1) = 1;
      geno_convert.at(1).at(2) = 2;
      geno_convert.at(1).at(3) = 3;
      maxLocusValue = 2;
      break;
  }
}


///
/// Calculates p value
/// @param z
/// @return p value
///
double LogisticRegression::norm(double z){
  double q = z * z;
  if(fabs(z)>7){
    return (1-1/q+3/(q*q))*exp(-q/2)/(fabs(z)*sqrt(PiD2));
  }
  else{
    return ChiSq(q, 1);
  }
}


///
/// Fills summary vector with totals for use
/// in logistic regression routine
/// @param genos vector<unsigned int> containing loci to analyze
/// @return
///
void LogisticRegression::summarize_data(vector<unsigned int> & genos)
{
  unsigned int combSize = genos.size();

  // clear and initialize arrays
  // set model
  initialize_summary(combSize);

  unsigned int currInd, currLoc;

  // establish a vector of correct size that can be used to distribute individuals
  vector<int> genotype(combSize,0);

  // determine indexes for unaffected and affected totals
  unsigned int unaffIndex = summary_data.at(0).size()-2;
  unsigned int numInds = set->num_inds();

  vector<int> ref_alleles(genos.size(), 0);
  // determine which geno_conversion to use for each locus
  for(unsigned int curr_mark=0; curr_mark < genos.size(); curr_mark++)
  {
    ref_alleles.at(curr_mark) = set->get_locus(genos.at(curr_mark))->getReferentIndex();
  }

  ngenotypes=0;

  // add to summary totals for each genotype
  // use current model to convert genotypes
  for(currInd=0; currInd < numInds; currInd++)
  {
	if(!(*set)[currInd]->isEnabled())
		continue;
    for(currLoc=0; currLoc < combSize; currLoc++)
    {
      genotype.at(currLoc) = geno_convert.at(ref_alleles.at(currLoc)).at((*set)[currInd]->get_genotype(set->get_locus(genos.at(currLoc))->getLoc()));
    }

    // increment count based on status of individual
    summary_data.at(indexConverter.flatten_indexes(genotype)).at(unaffIndex+(*set)[currInd]->getAffected())++;
    ngenotypes++;
  }

}

///
/// Sizes and clears arrays for holding data
/// @param currModelSize size of model
/// @return
///
void LogisticRegression::initialize_summary(unsigned int currModelSize){

  unsigned int array_size = indexConverter.get_size_array(currModelSize);

  // check to see if need to resize all parameters
  if(currModelSize != modelSize){
    modelSize = currModelSize;

    // establish vector for holding individual totals
    summary_data.assign(array_size, vector<double>(currModelSize,0));
    // set the values for the predictor variables
      zero_summary(array_size, currModelSize);
  }
  else{
    // zero out totals for summary data
      zero_summary(array_size, currModelSize);
  }

}

///
/// Returns index into array
/// @param j
/// @param k
/// @param nCols
/// @returns index
///
unsigned int LogisticRegression::ix(int j,int k,int nCols){
  return j * nCols + k;
}


///
///  Sets genotype for single array, adds interaction terms if
///  any needed and requested by user, zeroes out totals
///  @param array_size unsigned int number of rows in summary
///  @param currModelSize unsigned int current model size to work with
///  @return
///
void LogisticRegression::zero_summary(unsigned int array_size, unsigned int model_size){

  double product=1;
  for(unsigned int sub_array_index=0; sub_array_index < array_size; sub_array_index++){
    summary_data.at(sub_array_index) = indexConverter.decode_index_double(sub_array_index, model_size);

    // this version can handle any size model
    if(summary_data.at(sub_array_index).size() > 1 && includeInteractions){
      for(int i=int(interaction_lists.at(model_size).size())-1; i >= 0; i--){
        product=1;
        for(int j=int(interaction_lists.at(model_size).at(i).size())-1; j >= 0; j--){
          product*= summary_data.at(sub_array_index).at(interaction_lists.at(model_size).at(i).at(j));
        }
        summary_data.at(sub_array_index).push_back(product);
      }

      // when not full interaction remove the full interaction term from the list
      if(!fullInteraction){
        summary_data.at(sub_array_index).pop_back();
      }

    }
    summary_data.at(sub_array_index).push_back(0);
    summary_data.at(sub_array_index).push_back(0);
  }

}


///
/// Performs logistic regression on the snps and covariates
/// specified.  No interaction terms are included
/// @param loci vector pass empty if no markers included in analysis
/// @param covars vector pass empty if no covariates included in analysis
///
void LogisticRegression::calculate(vector<unsigned int>& loci, vector<unsigned int>& covars)
{
  vector<unsigned int> traits;
  calculate(loci,covars,traits);
}


///
/// Performs logistic regression on the snps and covariates
/// specified.  No interaction terms are included
/// @param loci vector pass empty if no markers included in analysis
/// @param covars vector pass empty if no covariates included in analysis
/// @param traits pass empty if no traits in analysis
///
void LogisticRegression::calculate(vector<unsigned int>& loci, vector<unsigned int>& covars, vector<unsigned int> & traits)
{

  unsigned int numLoci = loci.size();
  unsigned int numCovars = covars.size();
  unsigned int numTraits = traits.size();

  // determine size of row for each sample in dataset
  unsigned int row_size = numLoci + numCovars + numTraits + 1;
  if(includeInteractions)
    row_size++;

  vector<double> row(row_size, 0);

  // convert loci indexes to marker map
  vector<unsigned int> converted_loci = convert_loc_order(loci);

  // establish summary_data vector
  summary_data.clear();
  unsigned int numInds = set->num_inds();
  vector<int> includedCells;

  vector<int> ref_alleles(converted_loci.size(), 0);
  // determine which geno_conversion to use for each locus
  for(unsigned int curr_mark=0; curr_mark < converted_loci.size(); curr_mark++)
  {
    ref_alleles.at(curr_mark) = set->get_locus(loci.at(curr_mark))->getReferentIndex();
  }

  ngenotypes=0;
  unsigned int currInd, currValue, i;
  for(currInd=0; currInd < numInds; currInd++)
  {
	  if(!(*set)[currInd]->isEnabled() || skipInd.find(i) != skipInd.end())
		  continue;
    currValue = 0;
    bool any_missing = false;
    for(i=0; i < numLoci; i++)
    {
      if((*set)[currInd]->get_genotype(converted_loci.at(i)) != missingValue)
      {
        row.at(currValue++) = geno_convert.at(ref_alleles.at(i)).at((*set)[currInd]->get_genotype(converted_loci.at(i)));
      }
      else
      {
        any_missing = true;
        break;
      }
    }

    for(i=0; i < numCovars; i++)
    {
      if((*set)[currInd]->getCovariate(covars.at(i)) != missingCoValue)
        row.at(currValue++) = (*set)[currInd]->getCovariate(covars.at(i));
      else
      {
        any_missing = true;
        break;
      }
    }
    for(i=0; i < numTraits; i++)
    {
      if((*set)[currInd]->getTrait(traits.at(i)) != missingCoValue)
        row.at(currValue++) = (*set)[currInd]->getTrait(traits.at(i));
      else
      {
        any_missing = true;
        break;
      }
    }
    if(!any_missing)
    {
    	// for interactions swap the first 2 values
    	if(includeInteractions){
	    	row[row_size-2] = row[2];
  	  	row[2] = row[0] * row[1];
  	  	currValue++;
  	  }
      row.at(currValue) = Y[currInd];
      summary_data.push_back(row);
      includedCells.push_back(summary_data.size()-1);
      ngenotypes++;
    }
  }
  
// exit(1);

  calculateLR(summary_data, false, includedCells);
}

///
/// Indexes refer to the order of the markers in map location.
/// To use in sample need to convert them to the indexes in the Samples.
/// @param loci vector of unsigned int that will be converted
/// @return returns vector with updated indexes
///
vector<unsigned int> LogisticRegression::convert_loc_order(vector<unsigned int>& loci){
  // assume loci are in marker_map order so need to alter to order contained
  // in samples
  vector<unsigned int>::iterator iter;
  vector<unsigned int> converted_indexes;

  for(iter=loci.begin(); iter!=loci.end(); iter++){
    converted_indexes.push_back((*markers)[*iter]->getLoc());
  }

  return converted_indexes;
}

vector<unsigned int> LogisticRegression::convert_loc_order(vector<Marker*> loci){
	vector<unsigned int> converted_indexes;
	for(unsigned int i = 0; i < loci.size(); i++){
		converted_indexes.push_back(loci.at(i)->getLoc());
	}
	return converted_indexes;
}


///
/// Sets the parameters using StepOptions class
/// @param options StepOptions containing options
///
void LogisticRegression::set_parameters(StepOptions* options){
    setFullInteraction(options->getLRFullInteraction());
    setIncludeInteractions(options->getLRIncludeInteractions());
    setMaximumIterations(options->getLRMaximumIterations());
    setModelType(options->getLRModelType());
    // set phenotype/trait values
    setDependent(options);
}


///
/// Set trait values and individuals who will be skipped
///
///
void LogisticRegression::setDependent(StepOptions* options) {

  Y.clear();
  skipInd.clear();
  if(options->getUsePheno()){
    int index = options->getPhenoLoc();
    if (options->getPhenoName() != "") {
		  index = set->get_trait_index(options->getPhenoName());
		}   
		std::set<int> values;
		for (int i = 0; i < set->num_inds(); i++){
		  Y.push_back(set->get_sample(i)->getPheno(index));
			values.insert(Y[i]);
		}
  	if(values.find(2) != values.end()){
			for(vector<int>::iterator yIter=Y.begin(); yIter != Y.end(); ++yIter){
				*yIter -= 1;
			}
		}
  }
  else{
    for (int i = 0; i < set->num_inds(); i++){
      Y.push_back(set->get_sample(i)->getPheno()-1);
    }
  }

	for (int i = 0; i < set->num_inds(); i++){
		if(Y[i] < 0 || Y[i] > 1)
			skipInd.insert(i);
	}
  
}


///
/// Sets the model type to use in the calculation
/// @param modelType string containing model type to run
/// @throws Exception on error
///
void LogisticRegression::setModelType(string modelType){
  if(ModelTypeMap.find(modelType) != ModelTypeMap.end()){
    modType = ModelTypeMap[modelType];
  }
  else{
    throw MethodException(modelType + " is not a valid LR model type");
  }
  set_model();
}
}
