// https://www.luogu.com.cn/problem/P2901
// livin' for the hope of it all

#include <iostream>
#include <cstdint>
#include <cstring>
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
int h[N], e[M], ne[M], idx=0;
int rh[N], re[M], rne[M], ridx=0;
ll w[M], rw[M], d[N], ans[N];

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
        
        for (int a=rh[u]; ~a; a=rne[a])
        {
            int v=re[a];
            if (d[v]>d[u]+rw[a])
            {
                d[v]=d[u]+rw[a];
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
        for (int a=h[y]; ~a; a=ne[a])
        {
            int v=e[a];
            q.push({x+w[a], v});
        }
    }
}

int main()
{
    memset(h, -1, sizeof(h));
    memset(rh, -1, sizeof(rh));
    cin>>n>>m>>k;
    while (m--)
    {
        int x, y; ll z; cin>>x>>y>>z;
        e[idx]=y; w[idx]=z; ne[idx]=h[x]; h[x]=idx++;
        re[ridx]=x; rw[ridx]=z; rne[ridx]=rh[y]; rh[y]=ridx++;
    }
    dijkstra();
    astar();
    for (int a=1; a<=cnt; a++) cout<<ans[a]<<endl;
    for (int a=cnt+1; a<=k; a++) cout<<-1<<endl;
    return 0;
}