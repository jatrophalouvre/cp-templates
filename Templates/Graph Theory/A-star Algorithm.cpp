// https://www.luogu.com.cn/problem/P2901
#include <iostream>
#include <queue>
#include <vector>
#define int long long
#define fir first
#define sec second
using namespace std;
using PII=pair<int, int>;

const int N=100013;
int n, m, k;
int cnt=0;
vector<PII> s[N], rs[N];
int rd[N], ans[N];

struct node
{
    int d, u;
    bool operator<(const node x) const { return d+rd[u]>x.d+rd[x.u]; }
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
        
        for (auto [v, w]:rs[u])
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
        for (auto [v, w]:s[u]) q.push({d+w, v});
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
    for (int i=1; i<=cnt; i++) cout<<ans[i]<<endl;
    for (int i=cnt+1; i<=k; i++) cout<<-1<<endl;
    return 0;
}