//
//  EditDistanceFitness.cpp
//  GeneticAlgorithm
//
//  Created by Maxim Vainshtein on 14/05/2016.
//  Copyright © 2016 Maxim Vainshtein. All rights reserved.
//

#include "EditDistanceFitness.hpp"
#include "Chromosome.hpp"
#include <algorithm>

EditDistanceFitness::EditDistanceFitness(const std::string& query) :
Fitness(query)
{ }

size_t EditDistanceFitness::ResolveScore(const std::string& estimated_result,
                                         const std::string& real_result,
                                         const Chromosome& chromosome) const {
    
    if (estimated_result.length() != real_result.length()) return 0;
    
    const std::size_t len1 = estimated_result.size(), len2 = real_result.size();
    std::vector<std::vector<size_t>> d(len1 + 1, std::vector<size_t>(len2 + 1));
    
    d[0][0] = 0;
    for(size_t i = 1; i <= len1; ++i) d[i][0] = i;
    for(size_t i = 1; i <= len2; ++i) d[0][i] = i;
    
    for(size_t i = 1; i <= len1; ++i) {
        for(size_t j = 1; j <= len2; ++j) {
            
            d[i][j] = std::min({
                d[i - 1][j] + 1,
                d[i][j - 1] + 1,
                d[i - 1][j - 1] + (estimated_result[i - 1] == real_result[j - 1] ? 0 : 1)
            });
            
        }
    }
    
    //Less matches mean lower scores -> high matches high scores
    return real_result.length() - d[len1][len2];
}

size_t EditDistanceFitness::ResolveOptimalScore(const std::string &result) const {
    return result.length();
}

bool EditDistanceFitness::Descending() const { return false; }