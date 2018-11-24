#include <iostream>
#include <list>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
 #include <sys/time.h>

using namespace std;

int bucket(vector <double> a)
{

	int n;
	double x;
	double maxi;
	maxi = -1.0;

	n = a.size();
	vector <list <double> > b(n+1);

	for (int i = 0; i < n; i++) {
		
		maxi = max(a[i], maxi);

	}
	
	maxi++;

	for (int i = 0; i < n; i++) {
		a[i] = a[i] / maxi;
	}

	

	for (int i = 0; i < n; i++) {
		b[n * a[i]].push_back(a[i]);
	}

	for (int i = 0; i < n; i++) {
		b[i].sort();
	}
/*
	for (int i = 0; i < n; i++) {
		for (list <double>::iterator x = b[i].begin(); x != b[i].end(); x++) {
			cout << *x * maxi<<" ";
		}
		cout << endl;

	}
*/
}

int main()
{

	int n;
	double x;

    struct timeval strt_time, stop_time;
    double delay;

	srand(time(NULL));
	vector <double> a;

	for(int t = 0; t < 500; t++) {
		n = rand() % 500;
		vector <double> temp;
		swap(temp, a);
		for(int i = 0; i < n; i++) {
			x = rand() % 20000;
			a.push_back(x);
		}
		
		gettimeofday(&strt_time, NULL);
	  	bucket(a);
	    gettimeofday(&stop_time, NULL);

        delay = (stop_time.tv_sec - strt_time.tv_sec) * 1000.0;   // sec to ms
        delay += (stop_time.tv_usec - strt_time.tv_usec) / 1000.0;   // us to ms

        cout << n <<" "<< delay << endl;

	}


}


		


