#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

const int N = 100005;
int freq[N];
char c[N];
vector<int> encoding[N];
vector<int> temp;
vector<int> adj[N];

void dfs(int u)
{
	if(adj[u].size() == 0) // Leaf Node
	{
		for(int i = 0; i<temp.size(); i++)
			encoding[u].push_back(temp[i]);
		return;
	}
	
	for(int i = 0; i<adj[u].size(); i++)
	{
		temp.push_back(i);
		dfs(adj[u][i]);
		temp.pop_back();
	}
	return;
}

int main()
{
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);

	int n;
	cin >> n;
	for(int i = 1; i<=n; i++)
		cin >> c[i] >> freq[i];

	priority_queue<pii, vector<pii>, greater<pii> > pq; // data_type, container, comparator

	for(int i = 1; i<=n; i++)
		pq.push(make_pair(freq[i], i));

	int cnt = n;
	while(pq.size() != 1)
	{
		pii top1 = pq.top();
		pq.pop();
		pii top2 = pq.top();
		pq.pop();

		cnt++;
		pq.push(make_pair(top1.first + top2.first, cnt)); // (freq, index)

		adj[cnt].push_back(top1.second);
		adj[cnt].push_back(top2.second);
	}

	temp.clear();
	dfs(cnt);

	for(int i = 1; i<=n; i++)
	{
		cout << c[i] << " ";
		for(int j = 0; j<encoding[i].size(); j++)
			cout << encoding[i][j];
		cout << "\n";
	}

	return 0;
}