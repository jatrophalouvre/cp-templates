// https://www.luogu.com.cn/problem/P3387
// livin' for the hope of it all

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

using ll = long long;
const int N=100013, M=5000013;
int n, m;
int x[M], y[M];
vector<int> s[N], rs[N];
ll ov[N], val[N]={0};
bool vis[N]={0};
stack<int> st;
int g[N];
ll dp[N], ans;

void dfs_topo(int u)
{
    vis[u]=1;
    for (auto v:s[u]) if (!vis[v]) dfs_topo(v);
    st.push(u);
}
void dfs_scc(int u, int r)
{
    vis[u]=1; g[u]=r;
    val[r]+=ov[u];
    for (auto v:rs[u]) if (!vis[v]) dfs_scc(v, r);
}
void dfs_dp(int u)
{
    vis[u]=1;
    for (auto v:s[u])
    {
        if (!vis[v]) dfs_dp(v);
        dp[u]=max(dp[u], dp[v]);
    }
    dp[u]+=val[u];
}

int main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++) cin>>ov[a];
    for (int a=0; a<m; a++)
    {
        cin>>x[a]>>y[a]; x[a]--; y[a]--;
        s[x[a]].push_back(y[a]);
        rs[y[a]].push_back(x[a]);
    }
    
    for (int a=0; a<n; a++) if (!vis[a]) dfs_topo(a);
    memset(vis, 0, sizeof(vis));
    while (st.size())
    {
        int u=st.top(); st.pop();
        if (!vis[u]) dfs_scc(u, u);
    }
    
    for (int a=0; a<n; a++) s[a].clear();
    for (int a=0; a<m; a++)
    {
        if (g[x[a]]!=g[y[a]])
        {
            x[a]=g[x[a]]; y[a]=g[y[a]];
            s[x[a]].push_back(y[a]);
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
