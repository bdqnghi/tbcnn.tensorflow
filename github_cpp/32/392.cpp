\begin{lstlisting}
#define maxn 1000005
#define maxm 1000005

int id[maxm],eu[maxm],ev[maxm],ew[maxm],n,m,pnt[maxn];
int cmp(const int &i,const int &j){ return ew[i]<ew[j]; }
int find(int x){ if(x!=pnt[x]) pnt[x]=find(pnt[x]); return pnt[x]; }
    
int Kruskal()
{
    int ret=0,i,j,p;
    for(i=1;i<=n;i++) pnt[i]=i; // node[1..n]
    for(i=0;i<m;i++) id[i]=i;   // ew[0..m-1]
    std::sort(id,id+m,cmp);
    for(j=-1,i=1; i<n; i++){
        while( p=id[++j], find(eu[p])==find(ev[p]) );
        ret+=ew[p]; pnt[find(ev[p])]=find(eu[p]);
    }
    return ret;
}
\end{lstlisting}