// https://www.luogu.com.cn/problem/P1339
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll=long long;
using PII=pair<ll, ll>;

const int N=100013, W=1013;
int n, m;
vector<PII> g[N];
ll d[N];

void dial()
{
	bool vis[N]={0};
	for (int i=0; i<n; i++) d[i]=1e18;
	queue<int> q[W];
	
	q[0].push(0);
	d[0]=0;
	int cur=0, sz=1;
	while (sz>0)
	{
		while (!q[cur%W].size()) cur=(cur+1)%W;
		int u=q[cur].front(); q[cur].pop(); sz--;
		if (vis[u]) continue;
		vis[u]=1;
		
		for (auto [v, w]:g[u])
		{
			if (d[v]>d[u]+w)
			{
				d[v]=d[u]+w;
				q[d[v]%W].push(v); sz++;
			}
		}
	}
}

int main()
{
	cin>>n>>m;
	while (m--)
	{
		int u, v; ll w; cin>>u>>v>>w;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	
	dial();
	cout<<d[n-1]<<endl;
	return 0;
}