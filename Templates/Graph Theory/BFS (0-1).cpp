// https://www.luogu.com.cn/problem/P4667
#include <iostream>
#include <queue>
#define fir first
#define sec second
using namespace std;
using ll=long long;
using PII=pair<ll, ll>;

const int N=100013;
int n, m;
vector<PII> g[N];
ll d[N];

void bfs()
{
    for (int i=0; i<n; i++) d[i]=1e18;
    deque<int> q;
    
    q.push_back(0);
    d[0]=0;
    while (q.size())
    {
        int u=q.front(); q.pop_front();
        for (auto [v, w]:g[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                if (w==0) q.push_front(v);
                else q.push_back(v);
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
    
    bfs();
    cout<<d[n-1]<<endl;
    return 0;
}
