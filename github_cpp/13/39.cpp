






























#ifndef Volume_Utils_h
#define Volume_Utils_h

#include <vector>
#include <iostream>

namespace SLIVR {

#if defined(_WIN32) && !defined(uint)
  
#define uint unsigned
#endif






template <class T> inline
void SortIndex(T v[3], int i[3])
{
  T v_tmp; int i_tmp;
  i[0] = 0; i[1] = 1; i[2] = 2;
  if(v[0] > v[1]) {
    v_tmp = v[0]; v[0] = v[1]; v[1] = v_tmp;
    i_tmp = i[0]; i[0] = i[1]; i[1] = i_tmp;
  }
  if(v[1] > v[2]) {
    v_tmp = v[1]; v[1] = v[2]; v[2] = v_tmp;
    i_tmp = i[1]; i[1] = i[2]; i[2] = i_tmp;
  }
  if(v[0] > v[1]) {
    v_tmp = v[0]; v[0] = v[1]; v[1] = v_tmp;
    i_tmp = i[0]; i[0] = i[1]; i[1] = i_tmp;
  }
}


template <typename T, typename U> inline
void Sort(std::vector<T>& domain, std::vector<U>& range)
{
  for(unsigned int i=0; i<domain.size(); i++) {
    for(unsigned int j=i+1; j<domain.size(); j++) {
      if(domain[j] < domain[i]) {
        T domain_tmp = domain[i];
        domain[i] = domain[j];
        domain[j] = domain_tmp;
        U range_tmp = range[i];
        range[i] = range[j];
        range[j] = range_tmp;
      }
    }
  }
}


template <typename T, typename U> inline
void Sort(T* domain, U* range, int size)
{
  for(int i=0; i<size; i++) {
    for(int j=i+1; j<size; j++) {
      if(domain[j] < domain[i]) {
        T domain_tmp = domain[i];
        domain[i] = domain[j];
        domain[j] = domain_tmp;
        int range_tmp = range[i];
        range[i] = range[j];
        range[j] = range_tmp;
      }
    }
  }
}


template <class T> inline
void Sort(T* val, int n)
{
  for(int i=0; i<n; i++) {
    for(int j=i+1; j<n; j++) {
      if(val[j] < val[i]) {
        T val_tmp = val[i];
        val[i] = val[j];
        val[j] = val_tmp;
      }
    }
  }
}





template <typename T> inline
int MinIndex(T x, T y, T z)
{
  return x < y ? (x < z ? 0 : 2) : (y < z ? 1 : 2);
}


inline double Max(double d1, double d2)
{
  return d1>d2?d1:d2;
}

inline double Min(double d1, double d2)
{
  return d1<d2?d1:d2;
}


inline unsigned int Min(unsigned int d1, unsigned int d2)
{
    return d1<d2?d1:d2;
}

inline unsigned int Max(unsigned int d1, unsigned int d2)
{
    return d1>d2?d1:d2;
}


inline int Min(int d1, int d2)
{
    return d1<d2?d1:d2;
}

inline int Max(int d1, int d2)
{
    return d1>d2?d1:d2;
}


inline double Min(double d1, double d2, double d3)
{
    double m=d1<d2?d1:d2;
    m=m<d3?m:d3;
    return m;
}

inline double Mid(double a, double b, double c)
{
  return ((a > b) ? ((a < c) ? a : ((b > c) ? b : c)) : \
                    ((b < c) ? b : ((a > c) ? a : c)));
}

inline double Max(double d1, double d2, double d3)
{
    double m=d1>d2?d1:d2;
    m=m>d3?m:d3;
    return m;
}


inline bool IsPowerOf2(unsigned int n)
{
  return (n & (n-1)) == 0;
}





inline unsigned int
Pow2(const unsigned int dim) {
  if (IsPowerOf2(dim)) return dim;
  unsigned int val = 4;
  while (val < dim) val = val << 1;;
  return val;
}


inline double Clamp(double d, double min, double max)
{
  return d<=min?min:d>=max?max:d;
}

inline float Clamp(float d, float min, float max)
{
  return d<=min?min:d>=max?max:d;
}

inline int Clamp(int i, int min, int max)
{
  return i<min?min:i>max?max:i;
}

inline int Round(double d)
{
  return (int)(d+0.5);
}


inline double Abs(double d)
{
  return d<0?-d:d;
}

inline float Abs(float d)
{
  return d<0?-d:d;
}

inline int Abs(int i)
{
  return i<0?-i:i;
}

#define reimpliment_needed(x) \
  std::cerr << "*-*: REIMPLIMENT NEEDED :*-*: " \
            << __FILE__ << ":" << __LINE__ << std::endl;
 
} 

#endif 

