// https://www.luogu.com.cn/problem/P1339
// livin' for the hope of it all

#include <bits/stdc++.h>
#define int long long
using namespace std;

using PII = pair<int, int>;
const int N=100013, M=5000013, W=1013;
int n, m;
vector<PII> s[N];
int d[N];

void dial()
{
	bool vis[N]={0};
	for (int a=0; a<n; a++) d[a]=INT64_MAX;
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
		
		for (auto [v, w]:s[u])
		{
			if (d[v]>d[u]+w)
			{
				d[v]=d[u]+w;
				q[d[v]%W].push(v); sz++;
			}
		}
	}
}

signed main()
{
	cin>>n>>m;
	while (m--)
	{
		int x, y, z; cin>>x>>y>>z;
		s[x].push_back({y, z});
		s[y].push_back({x, z});
	}
	
	dial();
	cout<<d[n-1]<<endl;
	return 0;
}
