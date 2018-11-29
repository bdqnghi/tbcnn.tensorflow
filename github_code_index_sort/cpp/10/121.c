// -----------------------------------------------------------------------------
// Filename:    main.cpp
// Revision:    $Id$
// Description: this file contains the main program entry point.
// Created:     04/08/2016 03:20:29 PM
// Compiler:    G++
// Author:      Jason Meng (jm), jm652564@sju.edu
//
// Copyright (c) 2016 by Jason Meng, no rights reserved.
// -----------------------------------------------------------------------------


#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "headers/bucketsort.hpp"
#include "headers/utils.hpp"


using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using bucketsort::BucketSort;
using std::isnan;

static BucketSort * random_buckets(const int list_size, const int max_buckets) {
    BucketSort * bs = new BucketSort(list_size);

    for (int i = 0; i < max_buckets; ++i)
        bs->add(random_double(0, 1));

    return bs;
}


int main(int argc, char * argv[]) {
    int bucket_size = 5;
    int max_buckets = 20;

    cout << "***** New BucketSort, size=" << bucket_size;
    cout << ", length=" << max_buckets;
    cout << endl;
    BucketSort * bs = random_buckets(bucket_size, max_buckets);
    cout << *bs << endl;
    cout << "***** Add 10 random doubles" << endl;
    for (int i = 0; i < 10; ++i) {
        double data = random_double(0, 1);
        bs->add(data);
        cout << i << ": ";
        cout << "add(" << setprecision(6) << data << ")";
        cout << endl;
    }
    cout << "***** get(): Search data for 10 times at random index in range of [0, 50]" << endl;
    for (int i = 0; i < 10; ++i) {
        int index   = (int) random_double(0, 51);
        double data = bs->get(index);
        cout << i << ": ";
        cout << index << ": ";
        cout << "get(" << index << ")=";
        if (true == isnan(data))
            cout << "NAN";
        else
            cout << setprecision(6) << data;
        cout << endl;
    }

    #if defined(GRAD) && defined(EXTRA_CREDIT)
    cout << "***** get2(): Search data for 10 times at random index in range of [0, 50]" << endl;
    for (int i = 0; i < 10; ++i) {
        int index   = (int) random_double(0, 51);
        double data = bs->get2(index);
        cout << i << ": ";
        cout << index << ": ";
        cout << "get(" << index << ")=";
        if (true == isnan(data))
            cout << "NAN";
        else
            cout << setprecision(6) << data;
        cout << endl;
    }
    #endif // if defined(GRAD) && defined(EXTRA_CREDIT)

    cout << "***** Print out BucketSort" << endl;
    #ifdef GRAD
    cout << "BucketSort size: " << bs->size() << endl;
    cout << "Total # of Buckets: " << bs->length() << endl;
    cout << "Load Factor: " << setprecision(3) << bs->getLoadFactor();
    cout << endl;
    #endif
    cout << *bs;

    cout << endl;
    cout << "***** Finished running. Quit." << endl;
    delete bs;
    bs = nullptr;

    return 0;
} // main
