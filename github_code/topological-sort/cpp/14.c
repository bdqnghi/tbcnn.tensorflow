int n,m,i; int g[60][60],vis[60]; int p[60],ps;
int flag;
void dfs(int s)
{
	if(!flag)return;	vis[s]=-1;
	for(int i=1;i<=g[s][0];i++)
	{
		if(vis[g[s][i]]==-1)	{	flag=0;	return;	}
		if(vis[g[s][i]]==0) dfs(g[s][i]);
	}
	p[ps--]=s; vis[s]=1;
}
int main()
{
	int t; scanf("%d",&t);
	while (t--)
	{
		scanf("%d%d",&n,&m);
		for (i = 1; i <= n; i += 1)	g[i][0]=vis[i]=0;
		for (i = 0; i < m; i += 1)
		{	int u,v;	scanf("%d%d",&u,&v);		g[u][++g[u][0]]=v;		}
		ps=n; flag=1;
		for(i=1;flag && i<=n;i++)	if(! vis[i]) dfs(i);
		if(! flag)printf("-1");
		else for(i=1;i<=n;i++){if(i!=1)printf(" ");printf("%d",p[i]);}
		printf("\n");
	}
	return 0;
}
