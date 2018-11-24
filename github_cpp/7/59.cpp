#include <iostream>
#include <cassert>
#include "algol/perf/benchmark.hpp"

void tower_of_hanoi (char from, char to, char spare, std::size_t disks)
{
  using namespace std::literals::string_literals;

  if (disks < 1)
    throw std::domain_error{"tower of hanoi is defined only for positive numbers of disks"s};
  if (disks == 1) {
    //std::cout << from << " -> " << to << std::endl;
    return;
  }
  tower_of_hanoi(from, spare, to, disks - 1);
  tower_of_hanoi(from, to, spare, 1);
  tower_of_hanoi(spare, to, from, disks - 1);
}

int main ()
{
  using benchmark = algol::perf::benchmark<std::chrono::nanoseconds>;
  //tower_of_hanoi('A', 'B', 'C', 3);
  {
    auto result = benchmark::run_n(50000, tower_of_hanoi, 'A', 'B', 'C', 4);
    assert(result.size() == 50000);
    auto average = benchmark::run_average(result);
    std::cout << average << " 15 moves -> " << (average.duration.count() / 15) << " ns" << std::endl;
  }
  {
    auto result = benchmark::run_n(50000, tower_of_hanoi, 'A', 'B', 'C', 6);
    assert(result.size() == 50000);
    auto average = benchmark::run_average(result);
    std::cout << average << " 63 moves -> " << (average.duration.count() / 63) << " ns" << std::endl;
  }
  {
    auto result = benchmark::run_n(50000, tower_of_hanoi, 'A', 'B', 'C', 8);
    assert(result.size() == 50000);
    auto average = benchmark::run_average(result);
    std::cout << average << " 255 moves -> " << (average.duration.count() / 255) << " ns" << std::endl;
  }
  {
    auto result = benchmark::run_n(50000, tower_of_hanoi, 'A', 'B', 'C', 12);
    assert(result.size() == 50000);
    auto average = benchmark::run_average(result);
    std::cout << average << " 4095 moves -> " << (average.duration.count() / 4095) << " ns" << std::endl;
  }
  return 0;
}
