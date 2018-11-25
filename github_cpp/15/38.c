





using namespace std;
using namespace __gnu_cxx;





#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <list>
#include <map>
#include <set>
#include <bitset>
#include <functional>
#include <numeric>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <hash_map>
#include <stack>
#include <queue>
#include <limits.h>
#include <lib/constants/constants.h>
#include <lib/ds/commonds.h>
#include <lib/ds/linkedlistds.h>
#include <lib/ds/graphds.h>
#include <lib/ds/mathds.h>
#include <lib/ds/treeds.h>
#include <lib/utils/arrayutil.h>
#include <lib/utils/avltreeutil.h>
#include <lib/utils/bplustreeutil.h>
#include <lib/utils/btreeutil.h>
#include <lib/utils/commonutil.h>
#include <lib/utils/dillutil.h>
#include <lib/utils/graphutil.h>
#include <lib/utils/mathutil.h>
#include <lib/utils/redblacktreeutil.h>
#include <lib/utils/sillutil.h>
#include <lib/utils/treeutil.h>
#include <lib/utils/twofourtreeutil.h>









#ifndef MATRIXMULTIPLICATION_H_
#define MATRIXMULTIPLICATION_H_





vector<vector<int> > matrixMultiplication(vector<vector<int> > firstUserinput,vector<vector<int> > secondUserinput) {
    vector<vector<int> > result;
    if(firstUserinput.size() == 0 || secondUserinput.size() == 0) {
        return result;
    }
    if(firstUserinput[0].size() != secondUserinput.size()) {
        throw "Invalid input";
    }
    result.resize(firstUserinput.size());
    for(unsigned int counter = 0; counter < result.size(); counter++) {
        result[counter].resize(secondUserinput[0].size());
    }
    for(unsigned int rowCounter = 0; rowCounter < firstUserinput.size(); rowCounter++) {
        for(unsigned int columnCounter = 0; columnCounter < secondUserinput[0].size(); columnCounter++) {
            result[rowCounter][columnCounter] = 0;
        }
    }
    for(unsigned int rowCounter = 0; rowCounter < firstUserinput.size(); rowCounter++) {
        for(unsigned int columnCounter = 0; columnCounter < secondUserinput[0].size(); columnCounter++) {
            for(unsigned int counter = 0; counter < secondUserinput.size(); counter++) {
                result[rowCounter][columnCounter] += firstUserinput[rowCounter][counter] * secondUserinput[counter][columnCounter];
            }
        }
    }
    return result;
}

#endif 




