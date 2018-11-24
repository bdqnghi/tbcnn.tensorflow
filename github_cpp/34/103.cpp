/*******************************************************************************
* The MASH Framework contains the source code of all the servers in the
* "computation farm" of the MASH project (http://www.mash-project.eu),
* developed at the Idiap Research Institute (http://www.idiap.ch).
*
* Copyright (c) 2016 Idiap Research Institute, http://www.idiap.ch/
* Written by Charles Dubout (charles.dubout@idiap.ch)
*
* This file is part of the MASH Framework.
*
* The MASH Framework is free software: you can redistribute it and/or modify
* it under the terms of either the GNU General Public License version 2 or
* the GNU General Public License version 3 as published by the Free
* Software Foundation, whichever suits the most your needs.
*
* The MASH Framework is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public Licenses
* along with the MASH Framework. If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/


//------------------------------------------------------------------------------
/// @file classifier/NaiveBayes.cpp
/// @author Charles Dubout (charles.dubout@idiap.ch)
/// @date 2010.01.26
/// @version 1.7
//------------------------------------------------------------------------------

#include "NaiveBayes.h"

#include <cmath>
#include <functional>
#include <iomanip>
#include <numeric>
#include <sstream>

using namespace ML;

Classifier* NaiveBayes::clone() const {
	return new NaiveBayes(*this);
}

void NaiveBayes::train(InputSet& inputSet) {
	// Get the number of samples, features and labels
	const unsigned int nbSamples = inputSet.nbSamples();
	const unsigned int nbFeatures = inputSet.nbFeatures();
	const unsigned int nbLabels = inputSet.nbLabels();

	// Calculate the means, standard deviations, and class priors
	means_.clear();
	stds_.clear();
	priors_.clear();

	means_.resize(nbLabels * nbFeatures);
	stds_.resize(nbLabels * nbFeatures);
	priors_.resize(nbLabels);

	// Weighted calculation (http://en.wikipedia.org/wiki/Standard_deviation)
	unsigned int nonZero = 0;

	for(unsigned int s = 0; s < nbSamples; ++s) {
		const scalar_t* features = inputSet.features(s);
		const unsigned int label = inputSet.label(s);
		const scalar_t weight = inputSet.weight(s);

		if(weight > 0) {
			priors_[label] += weight;

			for(unsigned int f = 0; f < nbFeatures; ++f) {
				const scalar_t value = features[f];
				const unsigned int index = label * nbFeatures + f;
				const scalar_t mean = means_[index];

				means_[index] += weight * (value - mean) / priors_[label];
				stds_[index] += weight * (value - mean) * (value - means_[index]);
			}

			++nonZero;
		}
	}

	assert(nonZero);

	// Final division
	scalar_t norm = 0;

	for(unsigned int l = 0; l < nbLabels; ++l) {
		assert(priors_[l]);

		for(unsigned int f = 0; f < nbFeatures; ++f) {
			const unsigned int index = l * nbFeatures + f;

			stds_[index] = std::sqrt((nonZero * stds_[index]) /
									 ((nonZero - 1) * priors_[l]));
		}

		norm += priors_[l];
	}

	// Normalize the priors
	std::transform(priors_.begin(), priors_.end(), priors_.begin(),
				   std::bind2nd(std::divides<scalar_t>(), norm));

	// Remove a feature as soon as its standard deviation is 0 for one of the
	// label
	unsigned int nbZeros = 0;

	for(unsigned int f = 0; f < nbFeatures; ++f) {
		bool zero = false;

		for(unsigned int l = 0; l < nbLabels; ++l) {
			zero |= stds_[l * nbFeatures + f] <= 0;
		}

		if(zero) {
			for(unsigned int l = 0; l < nbLabels; ++l) {
				stds_[l * nbFeatures + f] = 0;
			}

			++nbZeros;
		}
	}

	// Make sure that there is still some features left
	assert(nbZeros < nbFeatures);
}

void NaiveBayes::distribution(InputSet& inputSet,
							  unsigned int sample,
				  			  scalar_t* distr) const {
	// Get the number of features and labels
	const unsigned int nbFeatures = inputSet.nbFeatures();
	const unsigned int nbLabels = inputSet.nbLabels();

	// Get the features of the sample to classify
	const scalar_t* features = inputSet.features(sample);

	// Fill distr with the probabilities that the sample is of every class
	const scalar_t sqrt2 = std::sqrt(scalar_t(2));

	for(unsigned int l = 0; l < nbLabels; ++l) {
		for(unsigned int f = 0; f < nbFeatures; ++f) {
			const unsigned int index = l * nbFeatures + f;

			if(stds_[index]) {
				scalar_t normVal = (features[f] - means_[index]) / stds_[index];
				distr[l] += std::log(priors_[l] / (sqrt2 * stds_[index])) -
							normVal * normVal / 2;
			}
		}
	}
}

void NaiveBayes::print(std::ostream& out) const {
	const unsigned int nbFeatures = stds_.size() / priors_.size();
	const unsigned int nbLabels = priors_.size();

	out << "Naive Bayes' classifier:" << std::endl;

	out << "Label         ";

	for(unsigned int l = 0; l < nbLabels; ++l) {
		out << " | " << std::setw(22) << l;
	}

	out << std::endl << "Prior         ";

	for(unsigned int l = 0; l < nbLabels; ++l) {
		out << " | " << std::setw(22) << priors_[l];
	}

	out << std::endl;

	for(unsigned int f = 0; f < nbFeatures; ++f) {
		if(stds_[f]) {
			out << "Feature " << std::setw(6) << f;

			for(unsigned int l = 0; l < nbLabels; ++l) {
				std::ostringstream oss;

				oss.precision(4);

				oss << means_[l * nbFeatures + f] << " +- "
					<< stds_[l * nbFeatures + f];

				out << " | " << std::setw(22) << oss.str();
			}

			out << std::endl;
		}
	}
}

void NaiveBayes::report(std::vector<unsigned int>& features) const {
	const unsigned int nbFeatures = stds_.size() / priors_.size();

	for(unsigned int f = 0; f < nbFeatures; ++f) {
		if(stds_[f]) {
			features.push_back(f);
		}
	}
}
