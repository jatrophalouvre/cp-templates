// https://www.luogu.com.cn/problem/P3388
// livin' for the hope of it all

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=100013, M=5000013;
int n, m;
vector<int> s[N];
int pre[N], low[N], i=0;
bool vis[N]={0}, cut[N]={0};

void tarjan(int u, int p)
{
	vis[u]=1;
	pre[u]=low[u]=i++;
	int cnt=0;
	
    for (auto v:s[u])
	{
		if (v==p) continue;
		if (!vis[v])
		{
			tarjan(v, u);
			low[u]=min(low[u], low[v]);
			if (low[v]>=pre[u] && u!=p) cut[u]=1;
			cnt++;
		}
		else low[u]=min(low[u], pre[v]);
	}
	if (cnt>=2 && u==p) cut[u]=1;
}

signed main()
{
	cin>>n>>m;
	while (m--)
	{
		int x, y; cin>>x>>y;
        s[x].push_back(y);
        s[y].push_back(x);
	}
	
	for (int a=0; a<n; a++) if (!vis[a]) tarjan(a, a);
    
	int ans=0;
	for (int a=0; a<n; a++) if (cut[a]) ans++; cout<<ans<<endl;
    for (int a=0; a<n; a++) if (cut[a]) cout<<a+1<<' '; cout<<endl;
	return 0;
}
