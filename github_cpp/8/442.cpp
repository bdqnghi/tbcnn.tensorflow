
/*Given an integer n, find the nth Fibonacci number F n .
Sample 1.
	Input:
	3
	Output:
	2
	Explanation:
	F3 = 2.

Sample 2.
	Input:
	10
	Output:
	55
	Explanation:
	F 10 = 55.*/
#include <iostream>
#include <cassert>

int fibonacci_naive(int n) {
    if (n <= 1)
        return n;

    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

 int fibonacci_fast(int n) {
     int a[n+1]={0};
	if(n<=1)
		a[n]=n;
	for(int i=2;i<=n;i++)
	{
		a[i]=a[i-1]+a[i-2];
	}
    return a[n];
}

void test_solution() {
    assert(fibonacci_fast(3) == 2);
    assert(fibonacci_fast(10) == 55);
    for (int n = 0; n < 20; ++n)
        assert(fibonacci_fast(n) == fibonacci_naive(n));
}

int main() {
    int n = 0;
    std::cin >> n;
//   std::cout << fibonacci_naive(n) << '\n';
//    test_solution();
   std::cout << fibonacci_fast(n) << '\n';
    return 0;
}
