//__INSERT_LICENSE__
// $Id: trysort5.cpp,v 1.8 2005/06/04 21:15:07 mstorti Exp $

#include <cstdlib>
#include <iostream>
#include <vector>
#include <aedsrc/util.h>
#include <aedsrc/sort.h>

using namespace std;
using namespace aed;

void aed::print2() {
  vector<int> &v = *w;  
  for (int j=0; j<v.size(); j++) 
    printf("%2d ",v[j]);
  printf("\n");
}

bool
less_than_abs(int &x,int &y) {
  return abs(x)<abs(y);
}

void 
make_random(vector<int> &v,int M1,int M2) {
  int N = v.size();
  assert(M2>M1);
  int s = M2-M1;
  for (int j=0; j<N; j++) 
    v[j] = M1 +irand(s);
}

void 
make_random(vector<int> &v,int M=20) {
  make_random(v,0,M);
}

bool check_sort(vector<int> &v,bool (*comp)(int&,int&)) {
  int size = v.size();
  for (int j=0; j<size-1; j++)
    if (comp(v[j+1],v[j+1])) return false;
  return true;
}

int main(int argc,char **argv) {

#if 0
  for (int it=0; it<20; it++) {
    int N=20;
    vector<int> v(N);
    for (int j=0; j<N; j++) v[j] = irand(2*N)-N;
    printf("--------------------\nantes de particiona: ");
    print(v);
    int pivot = v[0];
    printf("pivot: %d\n",pivot);
    partition(v.begin(),v.end(),less_than_abs,pivot);
    printf("despues de partition: ");
    print(v);
  }
#endif

#if 0
  for (int it=0; it<20; it++) {
    int 
      n1 = 1+irand(20),
      n2 = 1+irand(20),
      n = n1+n2;
    printf("n1: %d, n2 %d\n",n1,n2);
    vector<int> v(n);
    for (int j=0; j<n; j++) v[j]=j;
    cout << "antes de swap: ";
    print(v);
    vector<int>::iterator first = v.begin();
    range_swap<int>(first,first+n1,first+n);
    cout << "despues de swap: ";
    print(v);
  }
#endif
  
#if 1
  int N = 10;
  vector<int> v(N),vo,vos;
  w = &vo;
  for (int j=0; j<30; j++) {
    make_random(v,-N,N);
    // printf("before sorting\n");
    // print(v.begin(),v.end());

    vos = v;
    bubble_sort<int>(vos.begin(),vos.end(),less_than_abs);
    // printf("after sorting bubble\n");
    // print(vos.begin(),vos.end());

#if 1
    vo = v;
    quick_sort<int>(vo.begin(),vo.end(),less_than_abs);
    // printf("after sorting\n");
    // print(vo.begin(),vo.end());
    printf("quick-sort stable? %s\n",
	   (equivalent(vo,vos) ? "yes" : "no"));
#endif

#if 1
    vo = v;
    merge3_sort<int>(vo.begin(),vo.end(),less_than_abs);
    // printf("after sorting\n");
    // print(vo.begin(),vo.end());
    printf("merge3-sort stable? %s\n",
	   (equivalent(vo,vos) ? "yes" : "no"));
#endif

    vo = v;
    insertion_sort<int>(vo.begin(),vo.end(),less_than_abs);
    // printf("insertion-sort\n");
    // print(vo.begin(),vo.end());
    printf("insertion-sort stable? %s\n",
	   (equivalent(vo,vos) ? "yes" : "no"));

#if 1
    vo = v;
    selection_sort<int>(vo.begin(),vo.end(),less_than_abs);
    // printf("selection-sort\n");
    // print(vo.begin(),vo.end());
    printf("selection-sort stable? %s, OK? %s\n",
	   (equivalent(vo,vos) ? "yes" : "no"),
	   (equivalent(vo,vos,less_than_abs) ? "yes" : "no"));
#endif

#if 0
    printf("stable-sort\n");
    print(vos.begin(),vos.end());
    vo = v;
    heap_sort<int>(vo.begin(),vo.end(),less_than_abs);
    printf("heap-sort\n");
    print(vo.begin(),vo.end());
    printf("heap-sort stable? %s\n",
	   (equivalent(vo,vos) ? "yes" : "no"));
#endif

    printf("stable-sort\n");
    print(vos.begin(),vos.end());
    list<int> L;
    for (int j=0; j<v.size(); j++) L.insert(L.end(),v[j]);
    merge2_sort<int>(L,less_than_abs);
    for (int j=0; j<v.size(); j++) {
      vo[j] = *L.begin(); L.erase(L.begin());
    }
    printf("merge2-sort\n");
    print(vo.begin(),vo.end());
    printf("merge2-sort stable? %s\n",
	   (equivalent(vo,vos) ? "yes" : "no"));

#if 0
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>---: 
    printf("stable-sort\n");
    print(vos.begin(),vos.end());
    vo = v;
    shell_sort<int>(vo.begin(),vo.end(),less_than_abs);
    printf("shell-sort\n");
    print(vo.begin(),vo.end());
    printf("shell-sort stable? %s\n",
	   (equivalent(vo,vos) ? "yes" : "no"));
#endif

  }
#endif
}
