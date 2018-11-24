#include <algorithm>  /* max, min, next_permutation, prev_permutation */
#include <functional>  /* greater */
#include <list>
#include <numeric>  /* iota */
#include <sstream>  /* istringstream, ostringstream */
#include <stdexcept>  /* logic_error, invalid_argument */
#include <string>
#include <vector>
#include "Permutation.hpp"
#include "Groups/internals.hpp"  /* lcm, factorial */
using namespace std;

Permutation::Permutation() : pmap(0), _even(1), _order(1), _lehmer(0) { }

Permutation::Permutation(const vector<int>& mapping, int ev, int ord, int lehm)
  : pmap(mapping), _even(ev), _order(ord), _lehmer(lehm) {
 while (!pmap.empty() && pmap.back() == (int) pmap.size()) pmap.pop_back();
}

Permutation Permutation::identity() {return Permutation(); }

int Permutation::operator()(int i) const {
 if (0 < i && i <= (int) pmap.size()) return pmap[i-1];
 else return i;
}

Permutation Permutation::operator*(const Permutation& other) const {
 int newdeg = max(degree(), other.degree());
 vector<int> newmap(newdeg);
 for (int i=0; i<newdeg; i++) newmap[i] = (*this)(other(i+1));
 return Permutation(newmap, _even != -1 && other._even != -1 ? _even == other._even : -1);
}

Permutation& Permutation::operator*=(const Permutation& other) {
 *this = *this * other;
 return *this;
}

Permutation::operator string() const {
 vector< vector<int> > cycles = toCycles();
 if (cycles.empty()) return string("1");
 else {
  ostringstream out;
  for (size_t i=0; i<cycles.size(); i++) {
   out << '(';
   for (size_t j=0; j<cycles[i].size(); j++) {
    if (j>0) out << ' ';
    out << cycles[i][j];
   }
   out << ')';
  }
  return out.str();
 }
}

Permutation::operator bool() const {return !pmap.empty(); }

int Permutation::degree() const {return pmap.size(); }

Permutation Permutation::inverse() const {
 vector<int> newmap(pmap.size());
 for (size_t i=0; i<pmap.size(); i++) newmap[pmap[i]-1] = i+1;
 return Permutation(newmap, _even, _order);
}

int Permutation::order() const {
 if (_order == -1) {
  _order = 1;
  vector< vector<int> > cycles = toCycles();
  for (size_t i=0; i<cycles.size(); i++) {
   _order = Groups::lcm(_order, cycles[i].size());
  }
 }
 return _order;
}

bool Permutation::isEven() const {
 if (_even == -1) {
  size_t lensum = 0;
  vector< vector<int> > cycles = toCycles();
  for (size_t i=0; i<cycles.size(); i++) {
   lensum += cycles[i].size() - 1;
  }
  _even = lensum % 2 == 0;
 }
 return bool(_even);
}

bool Permutation::isOdd() const {return !isEven(); }

int Permutation::sign() const {return isEven() ? 1 : -1; }

int Permutation::lehmer() const {
 if (_lehmer == -1) {
  _lehmer = 0;
  list<int> left;
  for (int i=degree(); i>0; i--) left.push_back(i);
  for (int x=degree(); x>0; x--) {
   int y = (*this)(x);
   list<int>::iterator iter = left.begin();
   int i=0;
   while (*iter != y) {iter++; i++; }
   left.erase(iter);
   _lehmer = _lehmer * x + i;
  }
 }
 return _lehmer;
}

Permutation Permutation::fromLehmer(int x) {
 if (x < 0) throw invalid_argument("Permutation::fromLehmer: argument must be nonnegative");
 int x0 = x;
 vector<int> mapping;
 vector<int>::iterator iter;
 for (int f=1; x>0; x /= f++) {
  int c = x % f;
  for (iter = mapping.begin(); iter != mapping.end(); iter++) {
   if (*iter >= c) (*iter)++;
  }
  mapping.push_back(c);
 }
 for (iter = mapping.begin(); iter != mapping.end(); iter++) {
  *iter = mapping.size() - *iter;
 }
 return Permutation(mapping, -1, -1, x0);
}

vector< vector<int> > Permutation::toCycles() const {
 vector<int> cmap(pmap);
 vector< vector<int> > cycles;
 for (int i=0; i<(int)cmap.size(); i++) {
  if (cmap[i] != 0 && cmap[i] != i+1) {
   int x = i+1;
   vector<int> cyke(1, x);
   int y = cmap[x-1];
   cmap[x-1] = 0;
   while (y != x) {
    cyke.push_back(y);
    int next = cmap[y-1];
    cmap[y-1] = 0;
    y = next;
   }
   cycles.push_back(cyke);
  }
 }
 return cycles;
}

/* Returns the permutation representing the transposition of the positive
 * integers `a` and `b` */
Permutation Permutation::transposition(int a, int b) {
 if (a < 1 || b < 1) throw invalid_argument("Permutation::transposition: arguments must be positive");
 if (a == b) return Permutation();
 else {
  int big = max(a,b), small = min(a,b);
  vector<int> mapping(big);
  for (int i=0; i<big; i++)
   mapping[i] = i+1 == a ? b : i+1 == b ? a : i+1;
  /* For $a<b$, $Lehmer((a b)) = (b-a) (b-1)! + \sum_{i=a}^{b-2} i!$ */
  int lehmer = 0, fac = Groups::factorial(small);
  for (int i=small; i<big-1; i++) {
   lehmer += fac;
   fac *= i+1;
  }
  lehmer += fac * (big-small);
  return Permutation(mapping, 0, 2, lehmer);
 }
}

Permutation Permutation::firstOfDegree(int n) {
 return n <= 1 ? identity() : transposition(n, n-1);
}

/* This comparison method produces the same ordering as the modified Lehmer
 * codes. */
int Permutation::cmp(const Permutation& other) const {
 if (degree() < other.degree()) return -1;
 if (degree() > other.degree()) return  1;
 for (int i=degree()-1; i>=0; i--) {
  if (pmap[i] > other.pmap[i]) return -1;
  if (pmap[i] < other.pmap[i]) return 1;
 }
 return 0;
}

Permutation& Permutation::operator++() {
 if (degree() == 0) {
  *this = transposition(1,2);
 } else if (!next_permutation(pmap.rbegin(), pmap.rend(), greater<int>())) {
  *this = firstOfDegree(degree()+1);
 } else {
  _even = -1;
  _order = -1;
  if (_lehmer != -1) _lehmer++;
 }
 return *this;
}

Permutation Permutation::operator++(int) {
 Permutation tmp(*this);
 ++*this;
 return tmp;
}

Permutation& Permutation::operator--() {
 if (degree() == 0)
  throw logic_error("Permutation::operator--: cannot decrement identity");
 prev_permutation(pmap.rbegin(), pmap.rend(), greater<int>());
 while (!pmap.empty() && pmap.back() == (int) pmap.size()) pmap.pop_back();
 _even = -1;
 _order = -1;
 if (_lehmer != -1) _lehmer--;
 return *this;
}

Permutation Permutation::operator--(int) {
 Permutation tmp(*this);
 --*this;
 return tmp;
}

bool Permutation::disjoint(const Permutation& other) const {
 for (int i=0; i < min(degree(), other.degree()); i++) {
  if (i+1 != pmap[i] && i+1 != other.pmap[i]) return false;
 }
 return true;
}

vector<Permutation> Permutation::s_n(int degree) {
 if (degree < 0)
  throw invalid_argument("Permutation::s_n: argument must be nonnegative");
 vector<Permutation> elems(Groups::factorial(degree), identity());
 iota(elems.begin(), elems.end(), identity());
 return elems;
}

vector<int> Permutation::toImage(int n) const {
 //if (n <= degree()) return pmap;
 vector<int> imap(pmap);
 for (int i=degree()+1; i<=n; i++) imap.push_back(i);
 return imap;
}

Permutation Permutation::fromImage(const vector<int>& img) {
 vector<bool> used(img.size(), false);
 for (const int& x: img) {
  if (x < 1)
   throw invalid_argument("Permutation::fromImage: values must be positive");
  if (x > (int) img.size())
   throw invalid_argument("Permutation::fromImage: value missing from input");
  if (used[x-1])
   throw invalid_argument("Permutation::fromImage: value repeated in input");
  used[x-1] = true;
 }
 return Permutation(img);
}

Permutation Permutation::parse(const string& s) {
 istringstream in(s);
 char c;
 in >> ws;
 if (in >> c) {
  if (c == '(') {
   vector< vector<int> > cycles;
   for (;;) {
    vector<int> cyc;
    int i;
    while (in >> i) cyc.push_back(i);
    if (in.eof()) throw invalid_argument("Permutation::parse: string ended in mid-cycle");
    if (cyc.empty()) throw invalid_argument("Permutation::parse: no integer after opening parenthesis");
    in.clear();
    in >> ws;
    if ((in >> c) && c == ')') {
     cycles.push_back(cyc);
     in >> ws;
     if (in.eof()) return fromCycles(cycles.begin(), cycles.end());
     else if ((in >> c) && c == '(') continue;
     else throw invalid_argument("Permutation::parse: ')' not followed by '(' or end of string");
    } else throw invalid_argument("Permutation::parse: non-integer encountered in cycle");
   }
  } else if (c == '1') {
   in >> ws;
   if (in.eof()) return identity();
   else throw invalid_argument("Permutation::parse: initial '1' not followed by end of string");
  } else throw invalid_argument("Permutation::parse: string must begin with '1' or '('");
 } else throw invalid_argument("Permutation::parse: empty string");
}
