/*
 * ford_fulkerson.h
 *
 *  Created on: Jun 24, 2015
 *      Author: gian
 */

#ifndef FORD_FULKERSON_H_
#define FORD_FULKERSON_H_

#include "../base/digraph.h"
#include "../base/weightDij.h"
#include "../base/weightDijV.h"

namespace graphlib {

class Ford_Fulkerson {
public:
    Ford_Fulkerson();
    virtual ~Ford_Fulkerson();
    double execute(Digraph<WeightDijV, WeightDij> someGraph, std::string source, std::string end_t);
private:
    bool bfs(Digraph<WeightDijV, WeightDij> someGraph, std::string source, std::string end_t);

};

} /* namespace graphlib */

#endif /* FORD_FULKERSON_H_ */
