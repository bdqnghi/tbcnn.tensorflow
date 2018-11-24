#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>

using namespace std;

#define Pair pair<int, int>

struct disjoint_sets{
    int size;
    vector<int> pset;
    disjoint_sets(int n){
        size = n;
        pset = vector<int> (n);
        for (int i=0;i<n;i++)
            pset[i] = i;
    }

    int find_set(int s){
        if (pset[s]==s)
            return s;
        else return pset[s] = find_set(pset[s]);
    }

    void union_set(int a, int b){
        pset[find_set(a)] = find_set(b);
        size--;
    }

    int count(){
        return size;
    }
};

int N, Q, fV;
vector<Pair> edg;
int edges[3000000][2];
int mat [1003][1003];

int kruskal(){
    int sum = 0;
    disjoint_sets ds(N);
    sort(edg.begin(), edg.end());
    for (int i=0;i<edg.size();i++){
        if (ds.count()==1)
            return sum;
        int ind = edg[i].second;
        if (ds.find_set(edges[ind][0]-1)!=ds.find_set(edges[ind][1]-1)){
            sum+=edg[i].first;
            ds.union_set(edges[ind][0]-1,edges[ind][1]-1);
        }
    }
    return -1;
}

char inp[300000];
char tree[30000000];

int vis[1005];

void eat_spaces(int &ind){
    while(tree[ind]==' ')
        ind++;
}

int sizeT, cnt, cnnn, fin, cntE;

Pair parse_tree(int &ind){
    int sum = 0;
    eat_spaces(ind);
    if (tree[ind]=='(')
        ind++;
    else{
        int root = 0;
    while(tree[ind]>='0'&&tree[ind]<='9'){
        root = root*10 + (tree[ind]-'0');
        ind++;
    }
        return Pair(root,0);
    }
    eat_spaces(ind);
    int root = 0;
    while(tree[ind]>='0'&&tree[ind]<='9'){
        root = root*10 + (tree[ind]-'0');
        ind++;
    }
    if (vis[root]!=cnnn)
        cnt++;
    else fV = 1;
    vis[root] = cnnn;
    eat_spaces(ind);
    while(tree[ind]!=')'){
        if (tree[ind]=='('){
            Pair pp = parse_tree(ind);
            sum+=pp.second;
            sum+=mat[root][pp.first];
            cntE++;
            if (mat[root][pp.first]==0)
                fin = 1;
        }
        else {
            int num = 0;
            while(tree[ind]>='0'&&tree[ind]<='9'){
                num = num*10 + (tree[ind]-'0');
                ind++;
            }
            if (mat[root][num]==0)
                fin = 1;
            sum+=mat[root][num];
            cntE++;
            if (vis[num]!=cnnn)
                cnt++;
            else fV = 1;
            vis[num] = cnnn;
        }
        eat_spaces(ind);
    }
    ind++;
    //printf("RET: %d %d %d\n",ind,root,sum);
    return Pair(root,sum);
}


int main(){
    int cn = 1;
    gets(inp);
    sscanf(inp,"%d", &N);
    while(N){
        memset(mat,0,sizeof mat);
        edg.clear();
        int in, ii = 0;
        for (int i=1;i<N;i++){
            mat[i][i] = 0;
            gets(inp);
            int jj = 0, ss = strlen(inp);
            for (int j=i+1;j<=N;j++){
                while(inp[jj]==' ')
                    jj++;
                in = 0;
                while(jj<ss&&(inp[jj]>='0'&&inp[jj]<='9')){
                    in = in*10 + (inp[jj]-'0');
                    jj++;
                }
                mat[i][j] = in;
                mat[j][i] = in;
                if (in){
                    edges[ii][0] = i;
                    edges[ii][1] = j;
                    edg.push_back(Pair(in,ii));
                    ii++;
                }
            }
        }
        int mst = kruskal(), indi = 0;
        gets(inp);
        sscanf(inp,"%d", &Q);
        for (int i=1;i<=Q;i++){
            cnnn = i;
            cnt = 0;
            cntE = 0;
            fin = 0;
            fV = 0;
            gets(tree);
            if (mst==-1){
                printf("%d.%d NO\n",cn,i);
                continue;
            }
            indi = 0;
            //sizeT = strlen(tree);
            int ans = parse_tree(indi).second;
            //printf("ANS: %d %d %d %d\n", ans,fin,cnt, cntE);
            if (ans==mst&&!fin&&cnt==N&&cntE==N-1&&!fV){
                printf("%d.%d YES\n",cn,i);
            }
            else printf("%d.%d NO\n",cn,i);
        }
        memset(vis,0,sizeof vis);
        cn++;
        gets(inp);
        sscanf(inp,"%d", &N);
    }
}

/*
for (int i=1;i<=N;i++){
    for (int j=1;j<=N;j++)
        printf("%d ", mat[i][j]);
    printf("\n");
}
printf("MST: %d\n",mst);

4
4 2 1
4 0
3
5
(2 4 1)
(0000000000000000006 (  0000000003 ( 00000001 000000002) )  (0000000004 05) )
*/
