// https://codebreaker.xyz/problem/girlfriend (not solved)
// to be checked

#include <iostream>
#include <cstdint>
#include <cstring>
#include <stack>
using namespace std;

using ll = long long;
const int N=100013, M=5000013;
int n, m;
int h[N], e[M], ne[M], idx=0;
ll w[M], d[N];
bool vis[N];
stack<int> s;

void dfs(int u)
{
    vis[u]=1;
    for (int a=h[u]; ~a; a=ne[a])
    {
        int v=e[a];
        if (!vis[v]) dfs(v);
    }
    s.push(u);
}
void longest_path()
{
    memset(vis, 0, sizeof(vis));
    for (int a=0; a<n; a++) if (!vis[a]) dfs(a);
    for (int a=0; a<n; a++) d[a]=-INT64_MAX;
    
    memset(vis, 0, sizeof(vis));
    d[0]=0;
    vis[0]=1;
    while (s.size())
    {
        int u=s.top(); s.pop();
        if (d[u]==-INT64_MAX) continue;
        vis[u]=1;
        
        for (int a=h[u]; ~a; a=ne[a])
        {
            int v=e[a];
            if (d[v]<d[u]+w[a] && !vis[v])
            {
                d[v]=d[u]+w[a];
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
    }
    longest_path();
    cout<<d[n-1]<<endl;
    return 0;
}