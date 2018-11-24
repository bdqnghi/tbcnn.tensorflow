//
// Created by Vet Senthil on 3/10/2018.
//

#include "NaiveBayesClassifier.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <complex>
#include <math.h>

NaiveBayesClassifier::NaiveBayesClassifier() {
    probabilities = vector<vector<vector<double>>>(NUM_CLASSES
            ,vector<vector<double>>(Image::IMAGE_SIZE, vector<double>(Image::IMAGE_SIZE, 0)));

    priors = vector<double>(NUM_CLASSES);
    class_frequencies = vector<int>(NUM_CLASSES);
}

vector<Image> NaiveBayesClassifier::getTrainingImages() {
    return training_images;
}

vector<Image> NaiveBayesClassifier::getTestImages() {
    return test_images;
}

void NaiveBayesClassifier::setTrainingImages(vector<Image> images) {
    training_images = images;
}

void NaiveBayesClassifier::setTestImages(vector<Image> images) {
    test_images = images;
}

vector<int> NaiveBayesClassifier::getClassFrequencies() {
    return class_frequencies;
}

vector<double> NaiveBayesClassifier::getPriors() {
    return priors;
}

vector<vector<vector<double>>> NaiveBayesClassifier::getProbabilities() {
    return probabilities;
}

vector<Image> NaiveBayesClassifier::loadImageFeatures(const char *file_name) {
    vector<Image> images;

    ifstream imgs_file;
    imgs_file.open(file_name);

    if (!imgs_file) {
        cout << "File path not recognized" << endl;
    }

    vector<vector<bool>> image_features;
    string line;

    for(int i = 0; getline(imgs_file, line); i = (i + 1) % 28) {
        vector<bool> row(28, false);

        for (int j = 0; j < line.size(); ++j) {
            row[j] = (line[j] != ' ');
        }

        image_features.push_back(row);

        if (i == 27) {
            Image image(image_features);
            images.push_back(image);

            image_features.clear();
        }
    }

    imgs_file.close();
    return images;
}

vector<int> NaiveBayesClassifier::loadImageLabels(const char *file_name) {
    ifstream labels_file;
    labels_file.open(file_name);

    if (!labels_file) {
        cout << "File path not recognized" << endl;
    }

    vector<int> image_labels;
    string label;

    while (getline(labels_file, label)) {
        stringstream strstream(label);
        int label_num = 0;
        strstream >> label_num;

        image_labels.push_back(label_num);
    }

    labels_file.close();
    return image_labels;
}

vector<Image> NaiveBayesClassifier::loadImages(const char* img_file_name, const char* labels_file_name) {
    vector<Image> images;
    vector<int> labels;

    images = loadImageFeatures(img_file_name);
    labels = loadImageLabels(labels_file_name);

    for (int i = 0; i < images.size(); ++i) {
        images[i].setImageLabel(labels[i]);
    }

    return images;
}

void NaiveBayesClassifier::loadModel(const char* file_name) {
    ifstream model_file;
    model_file.open(file_name);

    if (!model_file) {
        cout << "File path not recognized" << endl;
    }

    string feature_probability;

    for (int i = 0; i < probabilities.size(); i++) {
        for (int j = 0; j < probabilities[0].size(); ++j) {
            for (int k = 0; k < probabilities[0][0].size(); ++k) {
                getline(model_file, feature_probability);
                probabilities[i][j][k] = stod(feature_probability);
            }
        }
    }

    string prior_value;

    for (int m = 0; m < priors.size(); ++m) {
        getline(model_file, prior_value);
        priors[m] = stod(prior_value);
    }

    model_file.close();
}

void NaiveBayesClassifier::saveModel(const char* file_name) {
    ofstream new_file;
    new_file.open(file_name);

    for (vector<vector<double>> class_features : probabilities) {
        for (vector<double> row_features : class_features) {
            for (double feature_value : row_features) {
                new_file << feature_value << endl;
            }
        }
    }

    for (double class_prior : priors) {
        new_file << class_prior << endl;
    }
}

void NaiveBayesClassifier::findClassFrequencies() {
    for (Image image : training_images) {
        class_frequencies[image.getImageLabel()]++;
    }
}

int NaiveBayesClassifier::getFeaturesSum(int class_num, int row, int col) {
    int feature_sum = 0;

    for (Image image : training_images) {
        if (image.getImageLabel() == class_num && image.getFeatures()[row][col]) {
            feature_sum += 1;
        }
    }

    return feature_sum;
}

void NaiveBayesClassifier::findProbabilities() {
    for (int i = 0; i < probabilities.size(); i++) {
        for (int j = 0; j < probabilities[0].size(); j++) {
            for (int k = 0; k < probabilities[0][0].size(); k++) {
                probabilities[i][j][k] = ((LAPLACE_VALUE + getFeaturesSum(i, j, k))
                                          / (2 * LAPLACE_VALUE + class_frequencies[i]));
            }
        }
    }
}

void NaiveBayesClassifier::findPriors() {
    for (int i = 0; i < priors.size(); ++i) {
        priors[i] = double(class_frequencies[i]) / training_images.size();
    }
}

vector<double> NaiveBayesClassifier::findLogPriors() {
    vector<double> log_priors;

    for (double &class_probability : priors) {
        log_priors.push_back(log(class_probability));
    }

    return log_priors;
}

int NaiveBayesClassifier::getMostProbableClass(vector<double> class_probabilities) {
    int class_num = 0;

    for (int i = 1; i < NUM_CLASSES; i++) {
        if (class_probabilities[i] > class_probabilities[class_num]) {
            class_num = i;
        }
    }

    return class_num;
}

double NaiveBayesClassifier::findImageClassProbability(Image img, int class_num) {
    Image& test_img = img;
    double class_probability;

    for (int i = 0; i < test_img.getFeatures().size(); ++i) {
        for (int j = 0; j < test_img.getFeatures()[0].size(); ++j) {
            if (test_img.getFeatures()[i][j]) {
                class_probability += log(probabilities[class_num][i][j]);
            } else {
                class_probability += log(1 - probabilities[class_num][i][j]);
            }
        }
    }
    return class_probability;
}

void NaiveBayesClassifier::classifyImages() {
    vector<double> class_probabilities;
    vector<double> initial_probabilities = findLogPriors();
    class_probabilities = initial_probabilities;

    for (int i = 0; i < test_images.size(); i++) {
        for (int j = 0; j < NUM_CLASSES; ++j) {
            class_probabilities[j] = findImageClassProbability(test_images[i], j);
        }

        test_images[i].setPredictedLabel(getMostProbableClass(class_probabilities));
        class_probabilities = initial_probabilities;
    }
}

double NaiveBayesClassifier::getAccuracyRate() {
    int num_correct_predictions = 0;

    for (auto &test_img : test_images) {

        cout << "Predicted Label: " << test_img.getPredictedLabel() << endl;
        cout << "Actual Label: " << test_img.getImageLabel() << endl;
        cout << endl;

        if (test_img.getPredictedLabel() == test_img.getImageLabel()) {
            num_correct_predictions++;
        }
    }

    return ((double)(num_correct_predictions) / test_images.size());
}

void NaiveBayesClassifier::printConfusionMatrix() {
    vector<double> test_class_frequencies(NUM_CLASSES,0);
    vector<vector<double>> confusion_matrix = vector<vector<double>>(NUM_CLASSES, vector<double>(NUM_CLASSES, 0));

    for (auto &test_img : test_images) {
        test_class_frequencies[test_img.getImageLabel()]++;
        confusion_matrix[test_img.getImageLabel()][test_img.getPredictedLabel()]++;
    }

    for (int i = 0; i < confusion_matrix.size(); ++i) {
        for (int j = 0; j < confusion_matrix[0].size(); ++j) {
            confusion_matrix[i][j] = (confusion_matrix[i][j] / test_class_frequencies[i]) * 100;
            confusion_matrix[i][j] = floor(confusion_matrix[i][j] * 100 + 0.5) / 100;

            cout << confusion_matrix[i][j] << "   ";
        }
        cout << endl;
    }
}