// https://www.luogu.com.cn/problem/P2901
// livin' for the hope of it all

#include <iostream>
#include <cstdint>
#include <queue>
#include <utility>
#include <vector>
#define fir first
#define sec second
using namespace std;

using ll = long long;
using PII = pair<ll, ll>;
const int N=100013, M=5000013;
int n, m, k;
int cnt=0;
vector<PII> s[N], rs[N];
ll d[N], ans[N];

struct node
{
    ll x, y;
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

int main()
{
    cin>>n>>m>>k;
    while (m--)
    {
        int x, y; ll z; cin>>x>>y>>z; x--; y--;
        s[x].push_back({y, z});
        rs[y].push_back({x, z});
    }
    
    dijkstra();
    astar();
    for (int a=1; a<=cnt; a++) cout<<ans[a]<<endl;
    for (int a=cnt+1; a<=k; a++) cout<<-1<<endl;
    return 0;
}
