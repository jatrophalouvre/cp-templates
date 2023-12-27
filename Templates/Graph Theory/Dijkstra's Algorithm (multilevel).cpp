// https://www.luogu.com.cn/problem/P4568
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
const int N=1000013, M=5000013;
int n, m, k, st, te;
int h[N], e[M], ne[M], idx=0;
ll w[M], d[N];

void add(int x, int y, ll z) { e[idx]=y; w[idx]=z; ne[idx]=h[x]; h[x]=idx++; }
void dijkstra()
{
    bool vis[N];
    memset(vis, 0, sizeof(vis));
    for (int a=0; a<n; a++) d[a]=INT64_MAX;
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    q.push({0, st});
    d[st]=0;
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
    cin>>n>>m>>k>>st>>te;
    while (m--)
    {
        int x, y; ll z; cin>>x>>y>>z;
        add(x, y, z); add(y, x, z);
        for (int a=1; a<=k; a++)
        {
            add(x+(a-1)*n, y+a*n, 0);
            add(y+(a-1)*n, x+a*n, 0);
            add(x+a*n, y+a*n, z);
            add(y+a*n, x+a*n, z);
        }
    }
    for (int a=1; a<=k; a++) add(te+(a-1)*n, te+a*n, 0);
    dijkstra();
    cout<<d[te+k*n]<<endl;
    return 0;
}