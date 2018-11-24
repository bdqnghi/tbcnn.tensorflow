#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <cstdlib>
#include <fstream>
#include <iomanip>   
#include <iostream>  
#include <sstream>  // istringstream buffer(myString);
#include <stack>
#include <algorithm>
#include <cstring>
#include <cassert>
using namespace std;
#define bit(x,i) (x&(1<<i))
#define lowbit(x) ((x)&((x)^((x)-1)))
//#define max(a,b) (a<b?b:a)
//#define abs(x) (x<0?-x:x)
#define IN(i,l,r) (l<i&&i<r)
#define LINR(i,l,r) (l<=i&&i<=r)
#define LIN(i,l,r) (l<=i&&i<r)
#define INR(i,l,r) (l<i&&i<r)
#define F(i,L,R) for (int i = L; i < R; i++)
#define FE(i,L,R) for (int i = L; i <= R; i++)
#define FF(i,L,R) for (int i = L; i > R; i--)
#define FFE(i,L,R) for (int i = L; i >= R; i--)
#define char2Int(c) (c-'0')
#define lastEle(vec) vec[vec.size()-1]
#define hBit(msb,n) asm("bsrl %1,%0" : "=r"(msb) : "r"(n))
#define clr(a,x) memset(a,x,sizeof(a))
#define getI(a) scanf("%d", &a)
#define getII(a,b) scanf("%d%d", &a, &b)
#define getIII(a,b,c) scanf("%d%d%d", &a, &b, &c)
#define getS(x) scanf("%s", x);
#define SZ(x) ((int)((x).size()))
#define REMAX(a,b) (a)=max((a),(b));
#define DBG(vari) cerr<<#vari<<" = "<<(vari)<<endl;
#define REMIN(a,b) (a)=min((a),(b));
#define FOREACH(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); i++)
#define ALL(t) t.begin(),t.end()
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define us unsigned short
#define IOS ios_base::sync_with_stdio(0);
#define pb push_back
#define INF 1001001001
#define PI 3.1415926535897932384626
#define mp make_pair
#define ll long long
#define fi first
#define se second
#define wez(n) int (n); scanf("%d",&(n));
#define wez2(n,m) int (n),(m); scanf("%d %d",&(n),&(m));
#define wez3(n,m,k) int (n),(m),(k); scanf("%d %d %d",&(n),&(m),&(k));
inline void pisz(int n) { printf("%d\n",n); }
#define TESTS wez(testow)while(testow--)
#define whileZ int T; getI(T); while(T--)
#define printA(a,L,R) FE(i,L,R) cout << a[i] << (i==R?'\n':' ')
#define printV(a) printA(a,0,a.size()-1)
#define MAXN 10000
#define sz(a) int((a).size()) 
#define pb push_back 
#define all(c) (c).begin(),(c).end() 
#define tr(c,i) for(typeof((c).begin() i = (c).begin(); i != (c).end(); i++) 
#define present(c,x) ((c).find(x) != (c).end()) 
#define cpresent(c,x) (find(all(c),x) != (c).end()) 
typedef int elem_t;
typedef vector<int> vi; 
typedef vector<vi> vvi; 
typedef pair<int,int> ii; 
template<typename T,typename TT> ostream& operator<<(ostream &s,pair<T,TT> t) {return s<<"("<<t.first<<","<<t.second<<")";}
template<typename T> ostream& operator<<(ostream &s,vector<T> t){F(i,0,SZ(t))s<<t[i]<<" ";return s; }
const int fx[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
class LRUCache{
struct Node{
    Node* next;
    Node* prev;
    int value;
    int key;
    Node(Node* p, Node* n, int k, int val): prev(p), next(n), key(k), value(val){};
    Node(int k, int val): prev(NULL), next(NULL), key(k), value(val){};
    Node(): prev(NULL), next(NULL){};
};
private:
    int capacity;
    map<int, Node*> M;
    Node* head;
    Node* tail;
public:
    LRUCache(int capacity):capacity(capacity) {
        M.clear();
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }
    void moveToTail(Node *cur, bool inList){
        if (inList){
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
        }
        tail->prev->next = cur;
        cur->prev = tail->prev;
        tail->prev = cur;
        cur->next = tail;
    }
    int get(int key) {
        if (M.find(key) == M.end())  
            return -1;
        else{
            moveToTail(M[key], true);
            return M[key]->value;
        }
    }
    void removeHead(){
        Node* temp = head->next;
        head->next->next->prev = head;
        head->next = head->next->next;
        free(temp);
    }
    void set(int key, int value) {
        if (M.find(key) != M.end()){ //found
            moveToTail(M[key], true);
            M[key]->value = value;
        }else{
            if (M.size() == capacity){
                M.erase(head->next->key);
                removeHead();
            }
            Node* cur = new Node(key, value);
            M[key] = cur;
            moveToTail(cur, false);
        }
    }
};
int main ( int argc, char *argv[] ) {
    
    LRUCache lru(10);
lru.set(10,13);
lru.set(3,17);
lru.set(6,11);
lru.set(10,5);
lru.set(9,10);
lru.get(13);
lru.set(2,19);
lru.get(2);
lru.get(3);
lru.set(5,25);
lru.get(8);
lru.set(9,22);
lru.set(5,5);
lru.set(1,30);
lru.get(11);
lru.set(9,12);
lru.get(7);
lru.get(5);
lru.get(8);
lru.get(9);
lru.set(4,30);
lru.set(9,3);
lru.get(9);
lru.get(10);
lru.get(10);
lru.set(6,14);
lru.set(3,1);
lru.get(3);
lru.set(10,11);
lru.get(8);
lru.set(2,14);
lru.get(1);
lru.get(5);
lru.get(4);
lru.set(11,4);
lru.set(12,24);
lru.set(5,18);
lru.get(13);
lru.set(7,23);
lru.get(8);
lru.get(12);
lru.set(3,27);
lru.set(2,12);
lru.get(5);
lru.set(2,9);
lru.set(13,4);
lru.set(8,18);
lru.set(1,7);
lru.get(6);
lru.set(9,29);
lru.set(8,21);
lru.get(5);
lru.set(6,30);
lru.set(1,12);
lru.get(10);
lru.set(4,15);
lru.set(7,22);
lru.set(11,26);
lru.set(8,17);
lru.set(9,29);
lru.get(5);
lru.set(3,4);
lru.set(11,30);
lru.get(12);
lru.set(4,29);
lru.get(3);
lru.get(9);
lru.get(6);
lru.set(3,4);
lru.get(1);
lru.get(10);
lru.set(3,29);
lru.set(10,28);
lru.set(1,20);
lru.set(11,13);
lru.get(3);
lru.set(3,12);
lru.set(3,8);
lru.set(10,9);
lru.set(3,26);
lru.get(8);
lru.get(7);
lru.get(5);
lru.set(13,17);
lru.set(2,27);
lru.set(11,15);
lru.get(12);
lru.set(9,19);
lru.set(2,15);
lru.set(3,16);
lru.get(1);
lru.set(12,17);
lru.set(9,1);
lru.set(6,19);
lru.get(4);
lru.get(5);
lru.get(5);
lru.set(8,1);
lru.set(11,7);
lru.set(5,2);
lru.set(9,28);
lru.get(1);
lru.set(2,2);
lru.set(7,4);
lru.set(4,22);
lru.set(7,24);
lru.set(9,26);
lru.set(13,28);
lru.set(11,26);
    return EXIT_SUCCESS;
}
