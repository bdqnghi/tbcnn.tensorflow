





#include "testcasefactory.h"


#include <assert.h>

void selectionSort( std::vector<int> &v ) {
    
}

int main() {
    TestCaseFactory tcf( 1024, 4096 );
    const int numTestCases = 1024;
    for ( int k = 0; k < numTestCases; ++k ) {
        std::vector<int> v = tcf.testCase();
        selectionSort( v );
        assert( TestCaseFactory::checkSorted( v ) );
    }
    return 0;
}
