// https://www.luogu.com.cn/problem/P3387
// livin' for the hope of it all

#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

using ll = long long;
const int N=100013, M=5000013;
int n, m;
int x[M], y[M];
int h[N], e[M], ne[M], idx=0;
int rh[N], re[M], rne[M], ridx=0;
ll os[N], s[N]={0};
bool vis[N]={0};
stack<int> st;
int g[N];
ll dp[N], ans;

void dfs_topo(int u)
{
    vis[u]=1;
    for (int a=h[u]; ~a; a=ne[a])
    {
        int v=e[a];
        if (!vis[v]) dfs_topo(v);
    }
    st.push(u);
}
void dfs_scc(int u, int r)
{
    vis[u]=1; g[u]=r;
    s[r]+=os[u];
    for (int a=rh[u]; ~a; a=rne[a])
    {
        int v=re[a];
        if (!vis[v]) dfs_scc(v, r);
    }
}
void dfs_dp(int u)
{
    vis[u]=1;
    for (int a=h[u]; ~a; a=ne[a])
    {
        int v=e[a];
        if (!vis[v]) dfs_dp(v);
        dp[u]=max(dp[u], dp[v]);
    }
    dp[u]+=s[u];
}

int main()
{
    memset(h, -1, sizeof(h));
    memset(rh, -1, sizeof(rh));
    cin>>n>>m;
    for (int a=0; a<n; a++) cin>>os[a];
    for (int a=0; a<m; a++)
    {
        cin>>x[a]>>y[a]; x[a]--; y[a]--;
        e[idx]=y[a]; ne[idx]=h[x[a]]; h[x[a]]=idx++;
        re[ridx]=x[a]; rne[ridx]=rh[y[a]]; rh[y[a]]=ridx++;
    }
    
    for (int a=0; a<n; a++) if (!vis[a]) dfs_topo(a);
    memset(vis, 0, sizeof(vis));
    while (st.size())
    {
        int u=st.top(); st.pop();
        if (!vis[u]) dfs_scc(u, u);
    }
    
    memset(h, -1, sizeof(h)); idx=0;
    for (int a=0; a<m; a++)
    {
        if (g[x[a]]!=g[y[a]])
        {
            x[a]=g[x[a]]; y[a]=g[y[a]];
            e[idx]=y[a]; ne[idx]=h[x[a]]; h[x[a]]=idx++;
        }
    }
    
    memset(vis, 0, sizeof(vis));
    for (int a=0; a<n; a++)
    {
        if (!vis[a]) dfs_dp(a);
        ans=max(ans, dp[a]);
    }
    cout<<ans<<endl;
    return 0;
}
