// https://www.luogu.com.cn/problem/P3366
// livin' for the hope of it all

#include <iostream>
#include <cstdint>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>
#define x first
#define y second
using namespace std;

using ll = long long;
using PII = pair<ll, ll>;
const int N=100013, M=5000013;
int n, m;
int h[N], e[M], ne[M], idx=0;
ll w[M];

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
        int u=q.top().y; q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        
        for (int a=h[u]; ~a; a=ne[a])
        {
            int v=e[a];
            if (!vis[v] && key[v]>w[a])
            {
                key[v]=w[a];
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
    memset(h, -1, sizeof(h));
    cin>>n>>m;
    while (m--)
    {
        int x, y; ll z; cin>>x>>y>>z;
        e[idx]=y; w[idx]=z; ne[idx]=h[x]; h[x]=idx++;
        e[idx]=x; w[idx]=z; ne[idx]=h[y]; h[y]=idx++;
    }
    
    cout<<prim()<<endl;
    return 0;
}