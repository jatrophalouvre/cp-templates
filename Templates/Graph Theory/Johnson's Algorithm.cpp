// https://www.luogu.com.cn/problem/P5905
#include <iostream>
#include <queue>
#include <vector>
#define int long long
#define fir first
#define sec second
using namespace std;
using PII = pair<int, int>;

const int N=3013;
int n, m;
vector<PII> s[N];
int d[N], rd[N];

bool spfa()
{
    bool inq[N]={0}; int cnt[N]={0};
    fill(rd, rd+n, 1e18);
    queue<int> q;
    
    q.push(n);
    rd[n]=0;
    inq[n]=1;
    cnt[n]=0;
    while (q.size())
    {
        int u=q.front(); q.pop();
        inq[u]=0;
        
        for (auto [v, w]:s[u])
        {
            if (rd[v]>rd[u]+w)
            {
                rd[v]=rd[u]+w;
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
    fill(d, d+n, 1e18);
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    q.push({0, src});
    d[src]=0;
    while (q.size())
    {
        int u=q.top().sec; q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        
        for (auto [v, w]:s[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                q.push({d[v], v});
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
    for (int v=0; v<n; v++) s[n].push_back({v, 0});
    
    if (!spfa())
    {
        cout<<-1<<endl;
        return 0;
    }
    
    for (int u=0; u<n; u++)
    {
        for (int i=0; i<s[u].size(); i++)
        {
            s[u][i].sec+=rd[u]-rd[s[u][i].fir];
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