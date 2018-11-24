#include "../KNearestNeighbours/KNearestNeighbours.h"
#include "../../../Utilities/Utilities.h"
#include "../../Point/IClusteringPoint.h"
#include "../../GenericVector/GenericVector.h"
#include "NaiveBayesClassification.h"

#include <vector>
#include <limits>
#include <iostream>

std::vector<std::vector<std::shared_ptr<IClusteringPoint>>> NaiveBayesClassification::getClassifiedPoints()
{
    std::vector<std::vector<std::shared_ptr<IClusteringPoint>>> result;

    //Prepping resultingClassifiedPoints 2d vector
    for (size_t i = 0; i < trainingClusters.size(); i++)
    {
        std::vector<std::shared_ptr<IClusteringPoint>> newEmptyCluster;
        result.push_back(newEmptyCluster);
    }

    for (std::shared_ptr<IClusteringPoint> &point : inputPoints)
    {
        int newClusterIndexForThisPoint = getPredictedClusterForPoint(point);
        result[newClusterIndexForThisPoint].push_back(point);
    }
    return result;
}

int NaiveBayesClassification::getPredictedClusterForPoint(std::shared_ptr<IClusteringPoint> &subjectPoint)
{
    map<int, double> finalProbabilities;
    map<int, float> priorProbabilities = createPriorProbabilityMap();
    map<int, float> neighboursLikelihoods = createNeighbourLikelihoodMap(subjectPoint);

    std::map<int, float>::iterator it;
    for (it = neighboursLikelihoods.begin(); it != neighboursLikelihoods.end(); ++it)
    {
        int currClusterId = it->first;
        finalProbabilities[currClusterId] = priorProbabilities[currClusterId] * neighboursLikelihoods[currClusterId];
    }

    //finding cluster with highest final probability, unfortunate loop repitition
    double highestFinalProbabilityYet = std::numeric_limits<double>::min();
    int clusterWithHighestFinalProbabilityYet = 0;

    std::map<int, double>::iterator it2;
    for (it2 = finalProbabilities.begin(); it2 != finalProbabilities.end(); ++it2)
    {
        if (it2->second > highestFinalProbabilityYet)
        {
            highestFinalProbabilityYet = it2->second;
            clusterWithHighestFinalProbabilityYet = it2->first;
        }
    }
    return clusterWithHighestFinalProbabilityYet;
}

std::map<int, float> NaiveBayesClassification::createPriorProbabilityMap()
{
    std::map<int, float> priorProbabilityMap;

    float sumOfAllClusterSizes = 0;
    for (std::vector<std::shared_ptr<IClusteringPoint>> cluster : trainingClusters)
        sumOfAllClusterSizes += cluster.size();

    for (size_t i = 0; i < trainingClusters.size(); i++)
    {
        std::vector<shared_ptr<IClusteringPoint>> currCluster = trainingClusters[i];
        float likelihoodToBeInThisCluster = currCluster.size() / sumOfAllClusterSizes;

        priorProbabilityMap.insert(make_pair(i, likelihoodToBeInThisCluster));
    }
    return priorProbabilityMap;
}

std::map<int, float> NaiveBayesClassification::createNeighbourLikelihoodMap(std::shared_ptr<IClusteringPoint> &subjectPoint)
{
    std::map<int, float> neighbourLikelihoodsPerCluster;

    //amount of neighbours was tested manually
    std::vector<std::shared_ptr<IClusteringPoint>> neighbours = KNearestNeighbours::getNearestNeighbours(subjectPoint, 7, trainingClusters);

    for (std::shared_ptr<IClusteringPoint> &neighbour : neighbours)
        neighbourLikelihoodsPerCluster[(*neighbour).getClusterId()] += 1;

    //dividing neighbour clusterCounts by the total amount of points per cluster
    std::map<int, float>::iterator it;
    for (it = neighbourLikelihoodsPerCluster.begin(); it != neighbourLikelihoodsPerCluster.end(); ++it)
    {
        int currClusterId = it->first;
        int totalAmountOfPointsInThisCluster = trainingClusters[currClusterId].size();

        it->second = it->second / totalAmountOfPointsInThisCluster;
    }
    return neighbourLikelihoodsPerCluster;
}
