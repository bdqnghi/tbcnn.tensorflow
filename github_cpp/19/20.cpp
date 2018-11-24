#include <ctime>
#include <iostream>
#include <random>
#include <vector>

std::vector<std::size_t> preprocesa(const std::string& p)
{
   std::vector<std::size_t> b = { std::size_t(-1) };
   for (std::size_t i = 0, j = -1; i < p.size( ); ++i) {
      while (j != -1 && p[j] != p[i]) {
         j = b[j];
      }

      b.push_back(++j);
   }

   return b;
}

std::size_t busca(const std::string& p, const std::string& t, const std::vector<std::size_t>& b)
{
   for (std::size_t i = 0, j = 0; i < t.size( ); ++i) {
      while (j != -1 && p[j] != t[i]) {
         j = b[j];
      }

      if (++j == p.size( )) {
         return i + 1 - p.size( );
      }
   }

   return std::string::npos;
}

int main( )
{
   std::string s = "abbabaabababaaabaaababbaaaababbabaaaba";
   std::string p = "bbaaaababba";

   auto pre = preprocesa(p);
   auto res = busca(p, s, pre);
   std::cout << res << "\n";
}
