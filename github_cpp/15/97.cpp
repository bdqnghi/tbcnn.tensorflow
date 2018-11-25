#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
#define DEB(x) cerr << "# " << (#x) << ": " << x << endl;
 
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
const int MAXN = 505, ITE = 50;
 
int A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN][MAXN], D[MAXN], BD[MAXN], CD[MAXN];
int main(){
        int n, i, j, k;
        bool ok;
        while(scanf("%d", &n) != EOF){
                for(i = 0; i < n; i++) for(j = 0; j < n; j++) scanf("%d", &A[i][j]);
                for(i = 0; i < n; i++) for(j = 0; j < n; j++) scanf("%d", &B[i][j]);
                for(i = 0; i < n; i++) for(j = 0; j < n; j++) scanf("%d", &C[i][j]);
                for(k = 0; k < ITE; k++){
                        for(i = 0; i < n; i++) D[i] = rand() % 200 - 100;
                        for(i = 0; i < n; i++){
                                BD[i] = 0;
                                for(j = 0; j < n; j++){
                                        BD[i] += D[j]*B[i][j];
                                }
                        }
                        for(i = 0; i < n; i++){
                                CD[i] = 0;
                                for(j = 0; j < n; j++){
                                        CD[i] += D[j]*C[i][j];
                                }
                        }
                        for(i = 0; i < n; i++){
                                D[i] = 0;
                                for(j = 0; j < n; j++){
                                        D[i] += BD[j]*A[i][j];
                                }
                        }
                        ok = true;
                        for(i = 0; i < n; i++){
                                if(D[i] != CD[i]) ok = false;
                        }
                        if(!ok) break;
                }
                printf("%s\n", (ok)?"YES":"NO");
        }
}
