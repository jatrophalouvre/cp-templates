// https://www.luogu.com.cn/problem/P3388
#include <iostream>
#include <vector>
#define int long long
using namespace std;

const int N=100013;
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
	
	for (int i=0; i<n; i++) if (!vis[i]) tarjan(i, i);
    
	int ans=0;
	for (int i=0; i<n; i++) if (cut[i]) ans++; cout<<ans<<endl;
    for (int i=0; i<n; i++) if (cut[i]) cout<<i+1<<' '; cout<<endl;
	return 0;
}