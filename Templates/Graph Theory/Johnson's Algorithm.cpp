// https://www.luogu.com.cn/problem/P5905
// livin' for the hope of it all

#include <iostream>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>
#define fir first
#define sec second
using namespace std;

using ll = long long;
using PII = pair<ll, ll>;
const int N=3013, M=150013;
int n, m;
int h[N], e[M], ne[M], idx=0;
ll w[M], rd[N], d[N];

bool spfa()
{
    bool inq[N]={0}; int cnt[N]={0};
    for (int a=0; a<N; a++) rd[a]=1e18;
    queue<int> q;
    
    q.push(n);
    rd[n]=0;
    inq[n]=1;
    cnt[n]=0;
    while (q.size())
    {
        int u=q.front(); q.pop();
        inq[u]=0;
        
        for (int a=h[u]; ~a; a=ne[a])
        {
            int v=e[a];
            if (rd[v]>rd[u]+w[a])
            {
                rd[v]=rd[u]+w[a];
                cnt[v]=cnt[u]+1;
                if (cnt[v]>n) return 0;
                if (!inq[v])
                {
                    q.push(v);
                    inq[v]=1;
                }
            }
        }
    }
    return 1;
}
void dijkstra(int src)
{
    bool vis[N]={0};
    for (int a=0; a<N; a++) d[a]=1e18;
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    q.push({0, src});
    d[src]=0;
    while (q.size())
    {
        int u=q.top().sec; q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        
        for (int a=h[u]; ~a; a=ne[a])
        {
            int v=e[a];
            if (d[v]>d[u]+w[a])
            {
                d[v]=d[u]+w[a];
                q.push({d[v], v});
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
        int x, y; ll z; cin>>x>>y>>z;
        e[idx]=y; w[idx]=z; ne[idx]=h[x]; h[x]=idx++;
        e[idx]=x; w[idx]=z; ne[idx]=h[y]; h[y]=idx++;
    }
    for (int v=0; v<n; v++) { e[idx]=v; w[idx]=0; ne[idx]=h[n]; h[n]=idx++; }
    
    if (!spfa())
    {
        cout<<-1<<endl;
        return 0;
    }
    
    for (int u=0; u<n; u++)
    {
        for (int a=h[u]; ~a; a=ne[a])
        {
            int v=e[a];
            w[a]+=rd[u]-rd[v];
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
