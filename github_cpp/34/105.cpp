// SYSTEM INCLUES


// C++ PROJECT INCLUDES
#include "Bayesian/NaiveBayesClassifier.hpp"

namespace Classifiers
{
namespace Bayesian
{

    NaiveBayesClassifier::NaiveBayesClassifier(std::string varName,
                StateFunctorPtr varNameFunctor, std::map<std::string,
                    StateFunctorPtr> featureNamesAndStates) :
        _varName(varName), _varNameFunctor(varNameFunctor),
        _nodes(), _featureNames()
    {
        this->_nodes[this->_varName] = std::make_shared<BayesianNode>(
                this->_varName, this->_varNameFunctor,
                DependencyType{}
            );
        this->_featureNames.reserve(featureNamesAndStates.size());
        for(auto it = featureNamesAndStates.begin(); it != featureNamesAndStates.end(); ++it)
        {
            this->_featureNames.push_back(it->first);
            this->_nodes[it->first] =
                std::make_shared<BayesianNode>(
                    it->first,
                    it->second,
                    DependencyType{
                        {this->_varName, this->_varNameFunctor}
                    }
                );
        }
    }

    NaiveBayesClassifier::~NaiveBayesClassifier()
    {
    }

    void NaiveBayesClassifier::Train(std::vector<
                std::map<std::string, std::string> >& trainingData)
    {
        BayesianNodePtr pNode = nullptr;
        StateFunctorPtr pFunctor = nullptr;
        int index = 0;
        std::map<std::string, std::string> argMap = {};
        std::map<std::string, std::string> emptyMap = {};
        for(auto& trainingTuple : trainingData)
        {
            for(auto it = trainingTuple.begin();
                it != trainingTuple.end(); ++it)
            {
                pNode = this->_nodes[it->first];
                pFunctor = pNode->_nameStateFunctor;

                if(it->first == this->_varName)
                {
                    index = pNode->ValuesToIndex(emptyMap);
                }
                else
                {
                    argMap = {{this->_varName, trainingTuple[this->_varName]}};
                    index = pNode->ValuesToIndex(argMap);
                }
                pNode->_table[index][pFunctor->Hash(it->second)] += 1.0;
            }
        }

        pNode = this->_nodes[this->_varName];
        for(auto it = this->_nodes.begin(); it != this->_nodes.end(); ++it)
        {
            if(it->first == this->_varName)
            {
                continue;
            }
            else
            {
                for(auto& state : it->second->_nameStateFunctor->GetAllStates())
                {
                    for(auto& varState : this->_varNameFunctor->GetAllStates())
                    {
                        argMap = {{this->_varName, varState}};
                        it->second->_table[it->second->ValuesToIndex(argMap)]\
                            [it->second->_nameStateFunctor->Hash(state)]\
                                /= pNode->AccessTable(emptyMap, varState);
                    }
                }
            }
        }

        for(int i = 0; i < pNode->_table[0].size(); ++i)
        {
            pNode->_table[0][i] /= trainingData.size();
        }
    }

    std::vector<std::string> NaiveBayesClassifier::Classify(std::map<std::string, std::string>& features)
    {
        double maxPr = 0.0;
        std::vector<std::pair<double, int> > classifications;
        double prOfClassification = 0.0;
        std::vector<std::string>& allStates = this->_varNameFunctor->GetAllStates();
        for(int i = 0; i < allStates.size(); ++i)
        {
            prOfClassification = this->PrOfState(features, allStates[i]);
            if(prOfClassification >= maxPr)
            {
                maxPr = prOfClassification;
                classifications.push_back(std::make_pair(prOfClassification, i));
            }
        }

        std::vector<std::string> solutions;
        for(int i = 0; i < classifications.size(); ++i)
        {
            if(std::get<0>(classifications[i]) == maxPr)
            {
                solutions.push_back(allStates[std::get<1>(classifications[i])]);
            }
            else
            {
                return solutions;
            }
        }
    }

    double NaiveBayesClassifier::PrOfState(std::map<std::string, std::string>& features,
                std::string& state)
    {
        double prob = this->_nodes[this->_varName]->PrOfState(state);

        std::map<std::string, std::string> argMap = {{this->_varName, state}};
        for(auto& feature : this->_featureNames)
        {
            prob *= this->_nodes[feature]->AccessTable(argMap, features[feature]);
        }
        return prob;
    }

} // end of namespace Bayesian
} // end of namespace Classifiers
