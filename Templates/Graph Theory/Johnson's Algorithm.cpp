// https://www.luogu.com.cn/problem/P5905
// to be reviewed
#include <iostream>
#include <queue>
#include <vector>
#define fir first
#define sec second
using namespace std;
using ll=long long;
using PII=pair<ll, ll>;

const int N=3013;
int n, m;
vector<PII> g[N];
ll d[N], rd[N];

bool spfa()
{
    bool inq[N]={0}; int cnt[N]={0};
    for (int i=0; i<n; i++) rd[i]=1e18;
    queue<int> q;
    
    q.push(n);
    rd[n]=0;
    inq[n]=1;
    cnt[n]=0;
    while (q.size())
    {
        int u=q.front(); q.pop();
        inq[u]=0;
        
        for (auto [v, w]:g[u])
        {
            if (rd[v]>rd[u]+w)
            {
                rd[v]=rd[u]+w;
                cnt[v]=cnt[u]+1;
                if (cnt[v]>n) return 1;
                if (!inq[v])
                {
                    q.push(v);
                    inq[v]=1;
                }
            }
        }
    }
    return 0;
}
void dijkstra(int src)
{
    bool vis[N]={0};
    for (int i=0; i<n; i++) d[i]=1e18;
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    q.push({0, src});
    d[src]=0;
    while (q.size())
    {
        int u=q.top().sec; q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        
        for (auto [v, w]:g[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                q.push({d[v], v});
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
    for (int v=0; v<n; v++) g[n].push_back({v, 0});
    
    if (spfa())
    {
        cout<<-1<<endl;
        return 0;
    }
    
    for (int u=0; u<n; u++)
    {
        for (int i=0; i<g[u].size(); i++)
        {
            g[u][i].sec+=rd[u]-rd[g[u][i].fir];
        }
    }
    for (int u=0; u<n; u++)
    {
        dijkstra(u);
        for (int v=0; v<n; v++)
        {
            if (d[v]==1e18) cout<<1e18<<' ';
            else cout<<d[v]+rd[v]-rd[u]<<' ';
        }
        cout<<endl;
    }
    return 0;
}