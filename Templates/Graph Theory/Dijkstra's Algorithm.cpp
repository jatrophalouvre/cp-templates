// https://www.luogu.com.cn/problem/P4779
#include <iostream>
#include <queue>
#include <vector>
#define int long long
#define fir first
#define sec second
using namespace std;
using PII=pair<int, int>;

const int N=100013;
int n, m;
vector<PII> s[N];
int d[N];

void dijkstra()
{
    bool vis[N]={0};
    fill(d, d+n, 1e18);
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    q.push({0, 0});
    d[0]=0;
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
        int u, v, w; cin>>u>>v>>w;
        s[u].push_back({v, w});
        s[v].push_back({u, w});
    }
    
    dijkstra();
    cout<<d[n-1]<<endl;
    return 0;
}