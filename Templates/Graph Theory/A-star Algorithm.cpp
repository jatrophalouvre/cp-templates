// https://www.luogu.com.cn/problem/P2901
// livin' for the hope of it all

#include <bits/stdc++.h>
#define int long long
#define fir first
#define sec second
using namespace std;

using PII = pair<int, int>;
const int N=100013, M=5000013;
int n, m, k;
int cnt=0;
vector<PII> s[N], rs[N];
int d[N], ans[N];

struct node
{
    int x, y;
    bool operator<(const node _) const { return x+d[y]>_.x+d[_.y]; }
};
void dijkstra()
{
    bool vis[N]={0};
    for (int a=0; a<n; a++) d[a]=1e18;
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    q.push({0, 0});
    d[0]=0;
    while (q.size())
    {
        int u=q.top().sec; q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        
        for (auto [v, w]:rs[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                q.push({d[v], v});
            }
        }
    }
}
void astar()
{
    priority_queue<node> q;
    
    q.push({0, n-1});
    while (q.size())
    {
        auto [x, y]=q.top(); q.pop();
        if (y==0)
        {
            cnt++; ans[cnt]=x;
            if (cnt==k) return;
            continue;
        }
        for (auto [v, w]:s[y])
        {
            q.push({x+w, v});
        }
    }
}

signed main()
{
    cin>>n>>m>>k;
    while (m--)
    {
        int x, y, z; cin>>x>>y>>z;
        s[x].push_back({y, z});
        rs[y].push_back({x, z});
    }
    
    dijkstra();
    astar();
    for (int a=1; a<=cnt; a++) cout<<ans[a]<<endl;
    for (int a=cnt+1; a<=k; a++) cout<<-1<<endl;
    return 0;
}
