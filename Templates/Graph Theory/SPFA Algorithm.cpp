// https://www.luogu.com.cn/problem/P4779
#include <iostream>
#include <queue>
#include <vector>
#define fir first
#define sec second
using namespace std;
using ll=long long;
using PII=pair<ll, ll>;

const int N=100013;
int n, m;
vector<PII> g[N];
ll d[N];

void spfa()
{
    bool inq[N]={0};
    for (int i=0; i<n; i++) d[i]=1e18;
    queue<int> q;
    
    q.push(0);
    d[0]=0;
    inq[0]=1;
    while (q.size())
    {
        int u=q.front(); q.pop();
        inq[u]=0;
        
        for (auto [v, w]:g[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                if (!inq[v])
                {
                    q.push(v);
                    inq[v]=1;
                }
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
    
    spfa();
    cout<<d[n-1]<<endl;
    return 0;
}