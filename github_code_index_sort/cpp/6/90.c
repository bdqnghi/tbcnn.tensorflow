/*
 * File:	radix.cpp
 *
 * Description:	Read a sequence of non-negative integers from the
 *		standard input and sort then using radix sort.  Each
 *		integer in the list is dropped into a bucket by its least
 *		significant digit.  After all integers are placed in
 *		buckets, the buckets are copied back into the list and we
 *		repeat the process, but with the next most significant
 *		digit.  After all digits have been processed, the list is
 *		sorted!  Since the buckets need to preserve the order of
 *		insertion, we need to implement a queue.  A deque provides
 *		this functionality for us.  The algorithm can be found at
 *		wikipedia.org/wiki/Radix_sort.
 */

# include <cmath>
# include <cstdlib>
# include <iostream>
# include "deque.h"

# define r 10

using namespace std;


/*
 * Function:	main
 *
 * Description:	Driver function for the radix application.
 */

int main(void)
{
    int i, x, niter, div, max;
    Deque a, dp[r];


    max = 0;


    /* Read in the numbers and record the maximum as we go along. */

    while (cin >> x) {
	if (x >= 0) {
	    a.addLast(x);

	    if (x > max)
		max = x;

	} else {
	    cerr << "Sorry, only non-negative values allowed." << endl;
	    exit(EXIT_FAILURE);
	}
    }

    div = 1;
    niter = ceil(log(max + 1) / log(r));

    while (niter --) {


	/* Move the numbers from the list to the buckets. */

	while (a.size() > 0) {
	    x = a.removeFirst();
	    dp[x / div % r].addLast(x);
	}


	/* Move the numbers from the buckets back into the list. */

	for (i = 0; i < r; i ++)
	    while (dp[i].size() > 0)
		a.addLast(dp[i].removeFirst());

	div = div * r;
    }


    /* Print out the numbers. */

    while (a.size() > 0)
	cout << a.removeFirst() << endl;

    return EXIT_SUCCESS;
}
