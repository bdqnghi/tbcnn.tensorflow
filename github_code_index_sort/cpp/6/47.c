//
// radix.cpp
//

#include "../sorters.hpp"

#include <array>
#include <algorithm>
#include <numeric>

template <typename E>
size_t bin(const E& elem, size_t digit) {
   return elem.size() > digit ? size_t(elem[digit]) + 1 : 0;
}

template <size_t R, typename C, typename P>
void radix_sort(P& pos, const C& data, size_t digit) {
   std::array<size_t, R + 1> count = {};
   P prev(pos);

   for (auto i : prev)
      ++count[bin(data[i], digit)];

   std::array<size_t, R + 1> done = {}, offset = {{0}};
   std::partial_sum(count.begin(), count.end() - 1, offset.begin() + 1);

   for (auto i : prev) {
      size_t b = bin(data[i], digit);
      pos[offset[b] + done[b]++] = i;
   }
}

struct shorter {
   template <typename A>
   bool operator()(const A& a, const A& b) { return a.size() < b.size(); }
};

template <size_t R, typename C>
std::vector<size_t> radix_sort(const C& data) {
   std::vector<size_t> pos(data.size());
   std::iota(pos.begin(), pos.end(), 0);

   size_t width = std::max_element(data.begin(), data.end(), shorter())->size();

   for (long digit = long(width) - 1; digit >= 0; --digit)
      radix_sort<R>(pos, data, size_t(digit));

   return pos;
}

void sorters::radix(std::vector<std::string>& v) {
   std::vector<std::string> tmp;
   std::vector<size_t> pos = radix_sort<128>(v);
   for (auto i : pos)
      tmp.push_back(v[i]);
   v = tmp;
}
