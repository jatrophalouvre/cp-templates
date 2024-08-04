// https://www.luogu.com.cn/problem/P2901
#include <iostream>
#include <queue>
#include <vector>
#define fir first
#define sec second
using namespace std;
using ll=long long;
using PII=pair<ll, ll>;

const int N=100013;
int n, m, k;
int cnt=0;
vector<PII> g[N], rg[N];
ll rd[N], ans[N];

struct node
{
    ll d; int u;
    bool operator<(const node _) const { return d+rd[u]>_.d+rd[_.u]; }
};
void dijkstra()
{
    bool vis[N]={0};
    for (int i=0; i<n; i++) rd[i]=1e18;
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    q.push({0, 0});
    rd[0]=0;
    while (q.size())
    {
        int u=q.top().sec; q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        
        for (auto [v, w]:rg[u])
        {
            if (rd[v]>rd[u]+w)
            {
                rd[v]=rd[u]+w;
                q.push({rd[v], v});
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
        auto [d, u]=q.top(); q.pop();
        if (u==0)
        {
            cnt++; ans[cnt]=d;
            if (cnt==k) return;
            continue;
        }
        for (auto [v, w]:g[u]) q.push((node){d+w, v});
    }
}

int main()
{
    cin>>n>>m>>k;
    while (m--)
    {
        int u, v; ll w; cin>>u>>v>>w;
        g[u].push_back({v, w});
        rg[v].push_back({u, w});
    }
    
    dijkstra();
    astar();
    for (int i=1; i<=cnt; i++) cout<<ans[i]<<endl;
    for (int i=cnt+1; i<=k; i++) cout<<-1<<endl;
    return 0;
}