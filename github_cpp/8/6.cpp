#include <iostream>
#include <cassert>
#include <vector>

int fibonacci_naive(int n) {
  if (n <= 1)
    return n;

  return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

int fibonacci_fast(int n) {
  int fibonacci[n];
  fibonacci[0] = 0;
  fibonacci[1] = 1;

  for(int i = 2; i <= n; i++){
   fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
  }

  return fibonacci[n];
}

int fibonacci_fast_low_memory(int n) {
  int fibonacci[2];
  fibonacci[0] = 0;
  fibonacci[1] = 1;

  if (n <= 1)
    return n;

  for(int i = 2; i <= n; i++){
    int tmp = fibonacci[1];
    fibonacci[1]= fibonacci[1] + fibonacci[0];
    fibonacci[0] = tmp;
  }

  return fibonacci[1];
}

void test_solution() {

  assert(fibonacci_fast(3) == 2);
  assert(fibonacci_fast(10) == 55);
  std::cout << "asserted!" << std::endl;
  for (int n = 0; n < 46; n++)
    {
      assert(fibonacci_fast_low_memory(n) == fibonacci_naive(n));
      std::cout << n <<  "asserted!" << std::endl;
    }
}

int main() {
  //int n = 0;
  //std::cin >> n;

  test_solution();
  //std::cout << fibonacci_fast_low_memory(n) << '\n';
  return 0;
}
