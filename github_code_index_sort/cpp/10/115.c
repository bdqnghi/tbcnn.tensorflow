#include "suffix_array.hpp"

namespace DS {

const int SuffixArray::MAX_VAL;
const size_t SuffixArray::npos;

void SuffixArray::build_sa() {
  if (s_.size() <= 1)
    return;

  auto n = s_.size();
  sa_.assign(n, 0);
  rank_.assign(n, 0);
  height_.assign(n, 0);

  vector<size_t> x(n, 0), y(n, 0), c(n, 0);
  size_t i;

  // bucket-sort by value
  for (i = 0; i < n; ++i)
    c[s_[i]]++;
  for (i = 1; i < c.size(); ++i)
    c[i] += c[i-1];
  for (i = n-1; i != npos; --i)
    sa_[--c[s_[i]]] = i;
  int r = 0;
  x[sa_[0]] = 0;
  for (i = 1; i < n; ++i)
    x[sa_[i]] = (s_[sa_[i]] == s_[sa_[i-1]]) ? r : ++r;

  // build sa
  for (size_t k = 1; k <= n; k<<=1) {
    // sort by the secondary key:
    // we want to sort the i's by x[i+k], and x[] was already sorted in sa_[],
    // thus the result: sa[n-k], ..., sa[n-1], sa[0], sa[1], ... , sa[n-k-1]
    size_t yp = 0;
    for (i = n-k; i < n; ++i)
      y[yp++] = i;
    for (i = 0; i < n; ++i) {
      if (sa_[i] >= k)
        y[yp++] = sa_[i]-k;
    }

    // bucket-sort by x[i]
    c.assign(n, 0);
    for (i = 0; i < n; ++i)
      c[x[i]]++;
    for (i = 1; i < c.size(); ++i)
      c[i] += c[i-1];
    for (i = n-1; i != npos; --i)
      sa_[--c[x[y[i]]]] = y[i];

    // store x[] to y[] and build the new x[]
    swap(x, y);

    size_t r = 0;
    x[sa_[0]] = 0;
    for (i = 1; i < n; ++i) {
      auto a = sa_[i], b = sa_[i-1];
      // We have to make sure that new_x[i] == new_x[j] iff
      // old_x[i] == old_x[j] && old_x[i+k] == old_x[j+k] (1). The reason is
      // if (1) holds, we would need to resolve this tie in the next round by
      // comparing new_x[i+k] and new_x[j+k], but not resolving it here.
      if ((y[a] == y[b])
          && ((a+k>n-1 && b+k>n-1)
              || (a+k<=n-1 && b+k<=n-1 && y[a+k] == y[b+k]))) {
        x[sa_[i]] = r;
      } else {
        x[sa_[i]] = ++r;
      }
    }
  }

  // fill-in final rank
  swap(x, rank_);
}

void SuffixArray::build_height() {
  // build height, from suffix[0] to suffix[n-1]
  size_t h = 0;
  height_[0] = 0;
  for (size_t i = 0; i < s_.size(); ++i) {
    if (rank_[i] == 0)
      continue;

    auto j = sa_[rank_[i]-1];
    if(h)
      h--;
    while (s_[i+h] == s_[j+h])
      h++;
    height_[rank_[i]] = h;
  }
}

void SuffixArray::build_lcp() {
  auto n = s_.size();

  for (size_t i = 0; i < n; ++i)
    lcp_cache_.emplace_back(n-i, npos);

  sparse_tbl_.emplace_back(n);
  for (size_t i = 0; i < n; ++i)
    sparse_tbl_[0][i] = height_[i];
  sparse_tbl_.emplace_back(n-1);

  for (size_t k = 1; (1<<k) <= n; ++k) {
    sparse_tbl_.emplace_back(n-(1<<k)+1);
    for (size_t i = 0; i <= n-(1<<k); ++i)
      sparse_tbl_[k][i] = std::min(sparse_tbl_[k-1][i],
                                   sparse_tbl_[k-1][i+(1<<(k-1))]);
  }
}

size_t SuffixArray::GetLCP(size_t ranka, size_t rankb) {
  if (ranka == npos || rankb == npos || ranka > rankb || rankb >= s_.size())
    return npos;
  if (ranka == rankb)
    return s_.size() - sa_[ranka];

  ranka++;
  if (lcp_cache_[ranka][rankb-ranka] != npos)
    return lcp_cache_[ranka][rankb-ranka];

  size_t k = 0, len = rankb-ranka+1;
  while ((1<<k) <= len)
    ++k;
  k--;

  return lcp_cache_[ranka][rankb-ranka] = std::min(sparse_tbl_[k][ranka],
                                                   sparse_tbl_[k][rankb-(1<<k)+1]);
}

size_t SuffixArray::Match(const string &s) {
  size_t lo = 0, hi = s_.size()-1, mid;
  size_t s_pos = 0, lcp = 0, ans = npos;

  while (lo <= hi) {
    mid = lo + (hi-lo)/2;
    size_t mp = sa_[mid], len = s_.size()-mp;

    if (lcp <= s_pos) {
      s_pos = lcp;
      while (s_pos < len && s_pos < s.size() && s[s_pos] == s_[mp+s_pos])
        s_pos++;
    }

    if (s_pos == s.size()) {
      ans = mid;
      break;
    } else if (mp+s_pos == len || s_[mp+s_pos] > s[s_pos]) {
      hi = mid-1;
      lcp = GetLCP(lo, mid);
    } else {
      lo = mid+1;
      lcp = GetLCP(mid, hi);
    }
  }

  if (ans != npos)
    return sa_[ans];
  else
    return npos;
}
}
