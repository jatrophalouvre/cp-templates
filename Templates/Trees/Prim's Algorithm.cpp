// https://www.luogu.com.cn/problem/P3366
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
int n, m;
vector<PII> s[N];

ll prim()
{
    int p[N]; ll key[N];
    bool vis[N]={0};
    for (int a=0; a<n; a++) key[a]=INT64_MAX;
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    q.push({0, 0});
    p[0]=0;
    key[0]=0;
    while (q.size())
    {
        int u=q.top().sec; q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        
        for (auto [v, w]:s[u])
        {
            if (!vis[v] && key[v]>w)
            {
                key[v]=w;
                p[v]=u;
                q.push({key[v], v});
            }
        }
    }
    
    ll ans=0;
    for (int u=1; u<n; u++) ans+=key[u];
    return ans;
}

int main()
{
    cin>>n>>m;
    while (m--)
    {
        int x, y; ll z; cin>>x>>y>>z;
        s[x].push_back({y, z});
        s[y].push_back({x, z});
    }
    
    cout<<prim()<<endl;
    return 0;
}
