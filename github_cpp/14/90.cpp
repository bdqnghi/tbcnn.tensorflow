

# include <cmath>
# include <cstdlib>
# include <iostream>
# include "deque.h"

# define r 10

using namespace std;




int main(void)
{
    int i, x, niter, div, max;
    Deque a, dp[r];


    max = 0;


    

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


	

	while (a.size() > 0) {
	    x = a.removeFirst();
	    dp[x / div % r].addLast(x);
	}


	

	for (i = 0; i < r; i ++)
	    while (dp[i].size() > 0)
		a.addLast(dp[i].removeFirst());

	div = div * r;
    }


    

    while (a.size() > 0)
	cout << a.removeFirst() << endl;

    return EXIT_SUCCESS;
}
