// https://www.luogu.com.cn/problem/P1339
// livin' for the hope of it all

#include <iostream>
#include <cstdint>
#include <cstring>
#include <queue>
using namespace std;

const int N=100013, M=5000013, W=1013;
int n, m;
int h[N], e[M], ne[M], idx=0;
int w[M], d[N];

void dial()
{
	bool vis[N]={0};
	for (int a=0; a<n; a++) d[a]=INT32_MAX;
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
		
		for (int a=h[u]; ~a; a=ne[a])
		{
			int v=e[a];
			if (d[v]>d[u]+w[a])
			{
				d[v]=d[u]+w[a];
				q[d[v]%W].push(v); sz++;
			}
		}
	}
}

int main()
{
	memset(h, -1, sizeof(h));
	cin>>n>>m;
	while (m--)
	{
		int x, y, z; cin>>x>>y>>z;
		e[idx]=y; w[idx]=z; ne[idx]=h[x]; h[x]=idx++;
		e[idx]=x; w[idx]=z; ne[idx]=h[y]; h[y]=idx++;
	}
	
	dial();
	cout<<d[n-1]<<endl;
	return 0;
}