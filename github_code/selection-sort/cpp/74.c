/***************************************************************************
                           selectionsort.cpp  -
                             -------------------
    begin                : Thu 30 Mar 2017 02:33:14 CDT
    copyright            : (c) 2017 by Akarsh Simha
    email                : akarsh.simha@kdemail.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


/* Project Includes */
#include "testcasefactory.h"

/* STL Includes */
#include <assert.h>

void selectionSort( std::vector<int> &v ) {
    // Implement selection sort here
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
