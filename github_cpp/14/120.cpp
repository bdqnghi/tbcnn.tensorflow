#include"logistic-regression.h"
#include<vector>
#include<omp.h>
#include<numeric>
using Eigen::MatrixXd;
using Eigen::VectorXi;
using Eigen::VectorXd;

LogisticRegression::LogisticRegression() {
	learning_rate_ = 0.001;
	train_epochs_ = 100;
	regularization_parameter_ = 0;
}

LogisticRegression::LogisticRegression(double learning_rate, double regularization_parameter, int train_epochs)
	: learning_rate_(learning_rate), regularization_parameter_(regularization_parameter), train_epochs_(train_epochs) {}

double LogisticRegression::learning_rate() const {
	return learning_rate_;
}

void LogisticRegression::learning_rate(double learning_rate) {
	this->learning_rate_ = learning_rate;
}

int LogisticRegression::train_epochs() const {
	return train_epochs_;
}

void LogisticRegression::train_epochs(int train_epochs) {
	this->train_epochs_ = train_epochs;
}

double LogisticRegression::regularization_parameter() const {
	return regularization_parameter_;
}

void LogisticRegression::regularization_parameter(double regularization_parameter) {
	this->regularization_parameter_ = regularization_parameter;
}

void LogisticRegression::SerialTrain(const MatrixXd &x, const VectorXi &y) {
	size_t num_examples = x.rows();
	size_t num_features = x.cols();
	theta_.setZero(num_features);

	for (size_t epoch = 0; epoch < train_epochs_; epoch++) {
		VectorXd gradient = VectorXd::Zero(num_features);
		for (size_t i = 0; i < num_examples; i++) {
			auto gradient_i = (Sigmoid(x.row(i) * theta_) - y(i)) * x.row(i);
			gradient += gradient_i;
		}
		regularize(gradient);
		gradient *= 1.0 / num_examples;
		theta_ -= learning_rate_ * gradient;
	}
}

void LogisticRegression::ParallelTrain(const MatrixXd &x, const VectorXi &y) {
	size_t num_examples = x.rows();
	size_t num_features = x.cols();
	theta_.setZero(num_features);
	VectorXd gradient = VectorXd::Zero(num_features);

	auto num_processors = omp_get_num_procs();
	size_t section_size = num_examples / num_processors;
	std::vector<VectorXd> partial_gradient(num_processors);
	std::vector<size_t> iterator(num_processors);

	for (size_t epoch = 0; epoch < train_epochs_; epoch++) {
		gradient.setZero(num_features);
		for (auto &item : partial_gradient) item.setZero(num_features);
		
#pragma omp parallel for
		for (int i = 0; i < num_processors; i++) {
			size_t &j = iterator[i];
			size_t left_bound = i * section_size;
			size_t right_bound = std::min((i + 1) * section_size, num_examples);
			for (j = left_bound; j < right_bound; j++) {
				auto gradient_row = (Sigmoid(x.row(j) * theta_) - y(j)) * x.row(j);
				partial_gradient[i] += gradient_row;
			}
		}
		gradient = std::accumulate(partial_gradient.begin(), partial_gradient.end(), gradient);
		regularize(gradient);
		gradient *= 1.0 / num_examples;
		theta_ -= learning_rate_ * gradient;
	}
}

void LogisticRegression::CacheUnfriendlyParallelTrain(const Eigen::MatrixXd & x, const Eigen::VectorXi & y) {
	size_t num_examples = x.rows();
	size_t num_features = x.cols();
	theta_.setZero(num_features);

	for (size_t epoch = 0; epoch < train_epochs_; epoch++) {
		VectorXd gradient = VectorXd::Zero(num_features);
#pragma omp parallel for
		for (int i = 0; i < num_examples; i++) {
			auto gradient_i = (Sigmoid(x.row(i) * theta_) - y(i)) * x.row(i);
#pragma omp critical
			gradient += gradient_i;
		}
		regularize(gradient);
		gradient *= 1.0 / num_examples;
		theta_ -= learning_rate_ * gradient;
	}
}

VectorXd LogisticRegression::PredictProbability(MatrixXd &x) const {
	VectorXd result = (x * theta_).unaryExpr(std::ptr_fun(LogisticRegression::Sigmoid));
	return std::move(result);
}

double LogisticRegression::Sigmoid(double x) {
	return 1.0 / (1.0 + std::exp(-x));
}

void LogisticRegression::regularize(VectorXd & gradient) {
	size_t length = gradient.rows();
	VectorXd theta_without_bias = theta_.block(1, 0, length - 1, 1);
	gradient.block(1, 0, length - 1, 1) += regularization_parameter_ * theta_without_bias;
}
