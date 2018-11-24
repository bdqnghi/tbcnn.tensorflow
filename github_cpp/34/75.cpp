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


/// \file	naive_bayes.cpp
/// \author Charles Dubout (charles.dubout@idiap.ch)
/// \date	Mar 21, 2011

#include "naive_bayes.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

using namespace ml;

NaiveBayes::NaiveBayes(double threshold) : threshold_(threshold) {
	// Make sure that threshold is strictly positive
	if (threshold <= 0.0) {
		throw std::invalid_argument("the threshold parameter must be strictly "
								 	"positive");
	}
}

IClassifier* NaiveBayes::clone() const {
	return new NaiveBayes(*this);
}

void NaiveBayes::train(const IDataSet& dataset) {
	// Get the number of samples, features, labels, and heuristics
	const unsigned int nbSamples = dataset.nbSamples();
	const unsigned int nbFeatures = dataset.nbFeatures();
	const unsigned int nbLabels = dataset.nbLabels();
	const unsigned int nbHeuristics = dataset.nbHeuristics();

	// Standard requirements
	if (nbSamples < 2 || !nbFeatures || nbLabels < 2 || !nbHeuristics) {
		throw std::invalid_argument("there must be at least 2 training samples, "
									"1 feature, 2 labels, and 1 heuristic");
	}

	// Assume that the features are new
	std::vector<double> priors(nbLabels, 0.0);
	std::vector<double> weights(nbFeatures, 0.0);
	std::vector<double> means(nbFeatures * nbLabels, 0.0);
	std::vector<double> stds(nbFeatures * nbLabels, 0.0);

	// Count the number of features per heuristic
	std::vector<unsigned int> heuristics(nbHeuristics, 0U);

	for (unsigned int f = 0; f < nbFeatures; ++f) {
		++heuristics[dataset.heuristic(f)];
	}

	// Set the weight of a feature as the inverse of the size of its heuristic
	for (unsigned int f = 0; f < nbFeatures; ++f) {
		weights[f] = 1.0 / heuristics[dataset.heuristic(f)];
	}

	// Get the features of one sample at a time
	std::vector<unsigned int> indices(nbFeatures);

	for (unsigned int f = 0; f < nbFeatures; ++f) {
		indices[f] = f;
	}

	std::vector<float> features(nbFeatures);

	// Calculate the means, standard deviations, and class priors
	for (unsigned int s = 0; s < nbSamples; ++s) {
		const unsigned int label = dataset.label(s);
		dataset.computeFeatures(1, &s, nbFeatures, &indices[0], &features[0]);

		priors[label] += 1.0;

		for (unsigned int f = 0; f < nbFeatures; ++f) {
			means[f * nbLabels + label] += features[f];
			stds[f * nbLabels + label] += features[f] * features[f];
		}
	}

	// Normalize the features' means and std deviations
	for (unsigned int f = 0; f < nbFeatures; ++f) {
		// Mean and variance of the feature
		double mean = 0.0;
		double variance = 0.0;

		for (unsigned int l = 0; l < nbLabels; ++l) {
			mean += means[f * nbLabels + l];
			variance += stds[f * nbLabels + l];
		}

		mean /= nbSamples;
		variance = (variance - nbSamples * mean * mean) / (nbSamples - 1);

		// Remove completely constant features
		if (variance < std::numeric_limits<double>::epsilon()) {
			weights[f] = 0.0;
			continue;
		}

		// Mean and standard deviation of the feature per label
		for (unsigned int l = 0; l < nbLabels; ++l) {
			if (priors[l]) {
				const unsigned int index = f * nbLabels + l;

				means[index] /= priors[l];
				stds[index] = (stds[index] - priors[l] * means[index] *
							   means[index]) / (priors[l] - 1.0);

				// Remove features that are constant for at least one label
				if (stds[index] < (threshold_ / nbLabels) *
								  (threshold_ / nbLabels) * variance) {
					weights[f] = 0.0;
					break;
				}
				else {
					stds[index] = std::sqrt(stds[index]);
				}
			}
		}
	}

	// Normalize the labels' priors
	for (unsigned int l = 0; l < nbLabels; ++l) {
		priors[l] /= nbSamples;
	}

	// Make sure that the priors are the same than during the previous training
	if (!priors_.empty() && priors != priors_) {
		throw std::invalid_argument("the classifiers was trained with different "
									"samples");
	}

	// Remove 'constant' features
	std::vector<unsigned int> reported;

	for (unsigned int f = 0, g = 0; f < nbFeatures; ++f) {
		if (weights[f]) {
			reported.push_back(f);

			if (g != f) {
				weights[g] = weights[f];

				for (unsigned int l = 0; l < nbLabels; ++l) {
					means[g * nbLabels + l] = means[f * nbLabels + l];
					stds[g * nbLabels + l] = stds[f * nbLabels + l];
				}
			}

			++g;
		}
	}

	if (reported.empty()) {
		throw std::range_error("all the features are 'constant' according "
							   "to the threshold parameter");
	}

	// Add the features to the classifier
	weights.resize(reported.size());
	means.resize(reported.size() * nbLabels);
	stds.resize(reported.size() * nbLabels);

	if (priors_.empty()) {
		priors_.swap(priors);
		weights_.swap(weights);
		means_.swap(means);
		stds_.swap(stds);
		reported_.swap(reported);
	}
	else {
		weights_.insert(weights_.end(), weights.begin(), weights.end());
		means_.insert(means_.end(), means.begin(), means.end());
		means.clear(); // Free means to make place for stds
		stds_.insert(stds_.end(), stds.begin(), stds.end());
		reported_.insert(reported_.end(), reported.begin(), reported.end());
	}
}

void NaiveBayes::distribution(const IDataSet& dataset,
							  unsigned int sample,
							  double* distr) const {
	// Get the number of features and labels
	const unsigned int nbFeatures = static_cast<unsigned int>(weights_.size());
	const unsigned int nbLabels = std::min(static_cast<unsigned int>(priors_.size()),
										   dataset.nbLabels());

	// Initialize the distribution
	std::fill_n(distr, dataset.nbLabels(), -std::numeric_limits<double>::infinity());

	for (unsigned int l = 0; l < nbLabels; ++l) {
		if (priors_[l]) {
			distr[l] = 0.0;
		}
	}

	// Get the features of the sample to classify
	std::vector<float> features(nbFeatures);
	dataset.computeFeatures(1, &sample, nbFeatures, &reported_[0], &features[0]);

	// Fill distr with the probabilities that the sample is of every class
	const double sqrt2pi = std::sqrt(2.0 * M_PI);

	for (unsigned int f = 0; f < nbFeatures; ++f) {
		if (weights_[f]) {
			for (unsigned int l = 0; l < nbLabels; ++l) {
				if (priors_[l]) {
					const unsigned int index = f * nbLabels + l;
					double normVal = (features[f] - means_[index]) / stds_[index];
					distr[l] += (std::log(priors_[l] / (sqrt2pi * stds_[index])) -
								 0.5 * normVal * normVal) * weights_[f];
				}
			}
		}
	}
}

void NaiveBayes::report(std::vector<unsigned int>& features) const {
	features.insert(features.end(), reported_.begin(), reported_.end());
}

void NaiveBayes::load(const json::Value& value) {
	if (value["name"].string() != "NaiveBayes") {
		throw std::invalid_argument("the input classifier is not NaiveBayes");
	}

	threshold_ = value["threshold"];
	priors_.assign(value["priors"].array().begin(), value["priors"].array().end());
	weights_.assign(value["weights"].array().begin(), value["weights"].array().end());
	means_.assign(value["means"].array().begin(), value["means"].array().end());
	stds_.assign(value["stds"].array().begin(), value["stds"].array().end());
	reported_.assign(value["reported"].array().begin(), value["reported"].array().end());
}

void NaiveBayes::save(json::Value& value) const {
	value["name"] = "NaiveBayes";
	value["threshold"] = threshold_;
	value["priors"].array().assign(priors_.begin(), priors_.end());
	value["weights"].array().assign(weights_.begin(), weights_.end());
	value["means"].array().assign(means_.begin(), means_.end());
	value["stds"].array().assign(stds_.begin(), stds_.end());
	value["reported"].array().assign(reported_.begin(), reported_.end());
}

void NaiveBayes::print(std::ostream& out) const {
	const unsigned int nbFeatures = static_cast<unsigned int>(weights_.size());
	const unsigned int nbLabels = static_cast<unsigned int>(priors_.size());

	std::ios_base::fmtflags flags = out.flags(std::ios::fixed);
	std::streamsize precision = out.precision(6);

	out << "Naive Bayes' classifier:" << std::endl;

	out << "Label               ";

	for (unsigned int l = 0; l < nbLabels; ++l) {
		out << " | " << std::setw(21) << l;
	}

	out << std::endl << "Prior               ";

	for (unsigned int l = 0; l < nbLabels; ++l) {
		out << " | " << std::setw(21) << priors_[l];
	}

	out << std::endl << "Feature |     Weight";

	for (unsigned int l = 0; l < nbLabels; ++l) {
		out << " |       Mean        Std";
	}

	out << std::endl;

	for (unsigned int f = 0; f < nbFeatures; ++f) {
		out << std::setw(7) << reported_[f] << " | "
			<< std::setw(10) << weights_[f];

		for (unsigned int l = 0; l < nbLabels; ++l) {
			out << " | " << std::setw(10) << means_[f * nbLabels + l] << ' '
				<< std::setw(10) << stds_[f * nbLabels + l];
		}

		out << std::endl;
	}

	out.flags(flags);
	out.precision(precision);
}
