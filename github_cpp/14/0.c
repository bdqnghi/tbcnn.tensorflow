#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

template <typename ForwardIterator>
void radixsort(ForwardIterator first, ForwardIterator last, int factor = 10)
{
   if (last-first-1 >= 1) {
      
      std::map<int, std::vector<int> > buckets;
      for (ForwardIterator i = first; i != last; ++i) {
         
         if (factor == 10) buckets[*i%factor].push_back(*i);
         else buckets[(*i/(factor/10)) %10].push_back(*i);
      }

      
      ForwardIterator copyfirst = first;
      for (int i = 0; i < 10; ++i) {
         for (std::vector<int>::const_iterator it = buckets[i].begin(); it != buckets[i].end(); )
            
            *copyfirst++ = *it++;
      }

      
      
      if (factor > *std::max_element(first, last)) return;
      radixsort(first, last, factor *= 10);
   }
}


template <typename ForwardIterator>
void negradixsort(ForwardIterator first, ForwardIterator last, int factor = 10)
{
   if (last-first-1 >= 1) {
      std::map<int, std::vector<signed int> > buckets;

      for (ForwardIterator i = first; i != last; ++i) {
         
         if (factor == 10) buckets[(*i%factor)*-1].push_back(*i);
         else buckets[((*i/(factor/10)) %10)*-1].push_back(*i);
      }

      ForwardIterator copyfirst = first;
      for (int i = 9; i >= 0; --i) {
         for (std::vector<int>::const_iterator it = buckets[i].begin(); it != buckets[i].end(); )
            
            *copyfirst++ = *it++;
      }

      if (factor > (*std::min_element(first, last))*-1) return;
      negradixsort(first, last, factor *= 10);
   }
}


template <typename ForwardIterator>
void signedradixsort(ForwardIterator first, ForwardIterator last)
{
   if (last-first-1 >= 1) {
      

      std::map<int, std::vector<signed int> > buckets;
      for (ForwardIterator i = first; i != last; ++i) {
         if (*i < 0) buckets[0].push_back(*i);
         else buckets[1].push_back(*i);
      }

      ForwardIterator copyfirst = first;
      ForwardIterator begOfpos;
      for (int i = 0; i < 2; ++i) {
         
         begOfpos = copyfirst;
         for (std::vector<signed int>::iterator it = buckets[i].begin(); it != buckets[i].end(); )
            *copyfirst++ = *it++;
      }

      
      radixsort(begOfpos, last);
      negradixsort(first, begOfpos);
   }
}

int main()
{
  std::vector<int> x = {-122, 311, 252, -41, -1, -1921, 12, 1, 92};

  std::cout << "Before sorting: ";
  for (std::vector<int>::iterator it = x.begin(); it != x.end(); ++it)
    std::cout << *it << " ";

  signedradixsort(x.begin(), x.end());

  std::cout << "\nAfter sorting: ";
  for (std::vector<int>::iterator it = x.begin(); it != x.end(); ++it)
    std::cout << *it << " ";
  std::cout << "\n";
}
