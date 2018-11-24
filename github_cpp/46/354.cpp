#include<bits/stdc++.h>
using namespace std;

// segment tree with data compression and lazy propagation
// this segment tree is specialized to be a sum segment tree

template<class T> class segment_tree{
   private:
           int qlo,qhi,N;
           T   V;
           map<int,T>tree,lazy;
           // replace with this if using c++11
           //unordered_map<int,T>tree,lazy;
   public:
         segment_tree(int _N){
            N = _N;
         }
         segment_tree(T arr[],int _N){
            N = _N; for(int i = 0;i < N;i++)
                update(i+1,arr[i]);
         }
         segment_tree(vector<T> arr,int _N){
            N = _N;
            for(int i = 0;i < N;i++)
                update(i+1,arr[i]);
         }
    public:
           // updating methods
           void update(int it,int v){// single point update
              qlo = qhi = it;
              V = v;
              _update(1,1,N);
           }
           void update(int it,int jt,T v){// range update
              qlo = it,qhi = jt;
              V = v;
              _update(1,1,N);
           }
           // querying methods
           T query(int it){
               qlo = qhi = it;
               return _query(1,1,N);
           }
           T query(int it,int jt){
               qlo = it, qhi = jt;
               return _query(1,1,N);
           }
     private:
             void _update(int n,int lo,int hi){
                  propagate(n,lo,hi);
                  if(lo > qhi || hi < qlo || lo > hi)
                     return;
                  else{
                      if(lo >= qlo && hi <= qhi){
                         tree[n] += abs(hi-lo+1)*V;
                         if(lo!=hi){
                            lazy[2*n]   += V;
                            lazy[2*n+1] += V;
                         }
                      }else{
                          _update(2*n,lo,(lo+hi)/2);
                          _update(2*n+1,(lo+hi)/2+1,hi);
                          tree[n] = tree[2*n]+tree[2*n+1];
                      }
                  }
             }
             T _query(int n,int lo,int hi){
                 propagate(n,lo,hi);
                 if(lo > qhi || hi < qlo || lo > hi)
                    return 0;
                 else if(lo >= qlo && hi <= qhi)
                    return tree[n];
                 else
                    return _query(2*n,lo,(lo+hi)/2)+_query(2*n+1,(lo+hi)/2+1,hi);
             }
             // helper methods
             void propagate(int n,int lo,int hi){
                if(lazy[n]!=0){
                    tree[n]  += abs(hi-lo+1)*lazy[n];
                    if(lo!=hi){
                       lazy[2*n]   += lazy[n];
                       lazy[2*n+1] += lazy[n];
                    }
                    lazy[n] = 0;
                }
             }
};

segment_tree<int> tree(1000);

int main(){
    //tree.update(0,500);
    //tree.update(9,1000);

    for(int i = 1;i <= 5;i++)
        tree.update(i,500);
    cout << tree.query(1,5) << endl;
    tree.update(1,5,500);

    cout << tree.query(1,5) << endl;
    cout << tree.query(1,2) << endl;
    cout << tree.query(1,3) << endl;
}
