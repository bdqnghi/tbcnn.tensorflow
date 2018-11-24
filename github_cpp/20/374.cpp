#include <iostream>
#include <mlpack/core.hpp>
#include <mlpack/methods/hmm/hmm.hpp>
#include <mlpack/methods/hmm/hmm_util.hpp>

#include <mlpack/methods/gmm/gmm.hpp>
//#include "team_id_processing.cpp"
//#include "month_id_processing.cpp"
//#include "data_IO.cpp"

using namespace mlpack;
using namespace mlpack::hmm;
using namespace mlpack::distribution;
using namespace mlpack::util;
using namespace mlpack::gmm;
using namespace mlpack::math;
using namespace arma;
using namespace std;

void hmm_train(const std::string &year, const std::string &team, const std::string col) {
	// input, hmm model and label file
        string inputFile = "state_data/"+ year + "/" + year + team + "_state_col" + col + ".csv";
      // string inputFile = "state_data/" + year + team + "_pca.csv";
	string modelFile = "hmm_data/hmm_model/" + year + "/" + year + team + "_model_col" + col + ".xml";
	string labelsFile =  "state_data/"+ year + "/" + year + team + "_state_label_col" + col + ".csv";
	//string labelsFile = "state_data/" + year + team +  "_label.csv";    
	string diffFile = "state_data/"+ year + "/" + year + team + "_state_diff_col" + col + ".csv";
	//std::cout<<diffFile<<endl;
	std::vector<std::vector<double> > state_data = file_read_formation_double (diffFile);
	//std::cout<<state_data.size()<<endl;

	RandomSeed((size_t) time(NULL));
	const int states = state_data[1][0];
  	const double tolerance = 1e-5;
	//const int states = 9;	
	//std::cout<<states<<endl;
	
        // Load the dataset(s) and labels.
	vector<mat> trainSeq;
	vector<arma::Col<size_t> > labelSeq; // May be empty.
        trainSeq.resize(1);
    	data::Load(inputFile, trainSeq[0], true);

        // Do we need to load labels?
        if (labelsFile != "")
        {
      		Mat<size_t> label;
      		data::Load(labelsFile, label, true);

      		// Ensure that matrix only has one column.
      		if (label.n_rows == 1)
        	label = trans(label);

      		if (label.n_cols > 1)
        	Log::Fatal << "Invalid labels; must be one-dimensional." << endl;

      		// Verify the same number of observations as the data.
      		if (label.n_elem != trainSeq[labelSeq.size()].n_cols)
        	Log::Fatal << "Label sequence " << labelSeq.size() << " does not have "<< "the same number of points as observation sequence "<< labelSeq.size() << "!" << endl;
      		labelSeq.push_back(label.col(0));
    	}
	//std::cout<<labelSeq.size()<<endl;

 	 // Now, train the HMM, since we have loaded the input data.
    	// Verify observations are valid.
	    for (size_t i = 0; i < trainSeq.size(); ++i){
	      if (trainSeq[i].n_rows > 1){
		std::cout << "Error in training sequence " << i << ": only "<< "one-dimensional discrete observations allowed for discrete "<< "HMMs!" << endl;
		}
	    }
	    // Do we have a model to preload?
	    HMM<DiscreteDistribution> hmm(1, DiscreteDistribution(1), tolerance);


      // Maximum observation is necessary so we know how to train the discrete distribution.
	     size_t maxEmission = 0;
	      for (vector<mat>::iterator it = trainSeq.begin(); it != trainSeq.end();
		   ++it)
	      {
		size_t maxSeq = size_t(as_scalar(max(trainSeq[0], 1))) + 1;
		if (maxSeq > maxEmission)
		  maxEmission = maxSeq;
	      }

      // Create HMM object.
      hmm = HMM<DiscreteDistribution>(size_t(states),DiscreteDistribution(maxEmission), tolerance);

   // std::cout<<labelSeq[0].size()<<endl;
    // Do we have labels?
    if (labelsFile == ""){
      hmm.Train(trainSeq); // Unsupervised training.
    } else {
      hmm.Train(trainSeq, labelSeq); // Supervised training.
    }
    // Finally, save the model.  This should later be integrated into the HMM
    // class itself.
    SaveRestoreUtility sr;
    SaveHMM(hmm, sr);
    sr.WriteFile(modelFile);




 /*  // gaussian distribution
    // Create HMM object.
    HMM<GaussianDistribution> hmm(1, GaussianDistribution(1), tolerance);

    // Do we have a model to load?
    size_t dimensionality = 0;

      // Find dimension of the data.
      dimensionality = trainSeq[0].n_rows;

	std::cout<<dimensionality<<endl;
      hmm = HMM<GaussianDistribution>(size_t(states), GaussianDistribution(dimensionality), tolerance);
   

    // Verify dimensionality of data.
    for (size_t i = 0; i < trainSeq.size(); ++i)
      if (trainSeq[i].n_rows != dimensionality)
        Log::Fatal << "Observation sequence " << i << " dimensionality ("<< trainSeq[i].n_rows << " is incorrect (should be "<< dimensionality << ")!" << endl;

    // Now run the training.
    if (labelsFile == "")
      hmm.Train(trainSeq); // Unsupervised training.
    else
      hmm.Train(trainSeq, labelSeq); // Supervised training.

    // Finally, save the model.  This should later be integrated into th HMM
    // class itself.
    SaveRestoreUtility sr;
    SaveHMM(hmm, sr);
    sr.WriteFile(modelFile);*/
 
}

void hmm_simulation(const std::string &year, const std::string &team, const std::string col) {
	  // Load observations.
	 //string inputFile = "state_data/" + year + team + "_state_col" + col + ".csv";
	string inputFile = "state_data/"+ year + "/" + year + team + "_state_col" + col + ".csv";
	string modelFile = "hmm_data/hmm_model/" + year + "/" + year + team + "_model_col" + col + ".xml";

	  mat dataSeq;
	  data::Load(inputFile, dataSeq, true);

	  // Load model, but first we have to determine its type.
	  SaveRestoreUtility sr;
	  sr.ReadFile(modelFile);
	  string type;
	  sr.LoadParameter(type, "hmm_type");

	  arma::Col<size_t> sequence;
	  if (type == "discrete")
	  {
	    HMM<DiscreteDistribution> hmm(1, DiscreteDistribution(1));

	    LoadHMM(hmm, sr);

	    // Verify only one row in observations.
	    if (dataSeq.n_cols == 1)
	      dataSeq = trans(dataSeq);

	    if (dataSeq.n_rows > 1)
	     std::cout<< "Only one-dimensional discrete observations allowed for "<< "discrete HMMs!" << endl;

	    hmm.Predict(dataSeq, sequence);
	  }   else if (type == "gaussian") {
	    HMM<GaussianDistribution> hmm(1, GaussianDistribution(1));

	    LoadHMM(hmm, sr);

	    // Verify correct dimensionality.
	    if (dataSeq.n_rows != hmm.Emission()[0].Mean().n_elem)
	      Log::Fatal << "Observation dimensionality (" << dataSeq.n_rows << ") "
		  << "does not match HMM Gaussian dimensionality ("
		  << hmm.Emission()[0].Mean().n_elem << ")!" << endl;

	    hmm.Predict(dataSeq, sequence);
	  }
	  else if (type == "gmm")
	  {
	    HMM<GMM<> > hmm(1, GMM<>(1, 1));

	    LoadHMM(hmm, sr);

	    // Verify correct dimensionality.
	    if (dataSeq.n_rows != hmm.Emission()[0].Dimensionality())
	      Log::Fatal << "Observation dimensionality (" << dataSeq.n_rows << ") "
		  << "does not match HMM Gaussian dimensionality ("
		  << hmm.Emission()[0].Dimensionality() << ")!" << endl;

	    hmm.Predict(dataSeq, sequence);
	  }
	 
	  // Save output.
	  string outputFile = "hmm_data/hmm_prediction/" + year + "/" + year + team + "_sim_col" + col + "_data" + ".csv";
	  data::Save(outputFile, sequence, true);

}

/*
int main()
{
	string year = "2014";
	//string team = "GSW";
	//string col = "0";
	//hmm_train(year, team, col);
	//hmm_simulation(year, team, col);
	std::vector<string> team = {"GSW", "BOS", "BKN", "NYK", "PHI", "TOR", "CHI","CLE", "DET", "IND", "MIL", "ATL", "CHA", "MIA", "ORL", "WAS", "DEN", "MIN", "OKC", "POR", "UTA", "GSW", "LAC", "LAL", "PHX", "SAC", "DAL", "HOU", "MEM", "NOP", "SAS"};	
	for (unsigned i = 0; i < team.size(); i++) {
		for (int j = 0; j < 20; j ++) {
			string col = std::to_string(j);
			hmm_train(year, team[i], col);
			hmm_simulation(year, team[i], col);
		}
	}

   return 1;
}*/
