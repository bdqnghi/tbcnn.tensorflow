#include "naive_bayes.h"
#include <iostream>

NaiveBayes::NaiveBayes(int m_featuresCount)
{
    classVariables.push_back(ClassVariable(true, m_featuresCount));
    classVariables.push_back(ClassVariable(false, m_featuresCount));
}

void NaiveBayes::train(const std::vector<double> &m_features, bool m_isAnomaly)
{
    if (m_isAnomaly) {
        classVariables[0].addRecord(m_features);
    } else {
        classVariables[1].addRecord(m_features);
    }
}

bool NaiveBayes::classify(const std::vector<double> &m_features, bool m_appendData)
{
    if (classVariables[0].posterior(m_features) > classVariables[1].posterior(m_features)) {
        if (m_appendData) classVariables[0].addRecord(m_features);
        return true;
    } else {
        if (m_appendData) classVariables[1].addRecord(m_features);
        return false;
    }
}

void NaiveBayes::learn(std::vector<std::vector<double> > &set, std::vector<bool> &target)
{
    for (int i = 0; i < set.size(); i++) train(set[i], target[i]);
}

std::vector<bool> NaiveBayes::test(std::vector<std::vector<double> > &set)
{
    std::vector<bool> results;
    for (int i = 0; i < set.size(); i++) results.push_back(classify(set[i], false));
    return results;
}
