#define MX 1001 
int n,m;
vector<pair<int,pair<int,int> > >vpp;   //weight,edge1,edge2
int par[MX],rank[MX];
int find(int x){
    if(par[x]!=x)
        par[x]=find(par[x]);
    return par[x];
}
void Union(int x,int y){
    int px=find(x);
    int py=find(y);
    if(rank[px]<rank[py])
        par[px]=py;
    else if(rank[px]>rank[py])
        par[py]=px;
    else{
        par[px]=py;
        rank[py]++;
    }
}
int kruskal(){
    sort(vpp.begin(),vpp.end());
    int result,x,y;
    for(int i=0;i<m;i++){
        pair<int,pair<int,int> > ppii=vpp[i];
        x=ppii.second.first;
        y=ppii.second.second;
        if(par[x]!=par[y]){
            Union(x,y);
            result+=ppii.first;
        }
    }
    return result;
}
