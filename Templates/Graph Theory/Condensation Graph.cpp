// https://www.luogu.com.cn/problem/P3387
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
using ll=long long;

const int N=100013, M=5000013;
int n, m;
int x[M], y[M];
vector<int> g[N], rg[N];
ll a[N], val[N]={0};
bool vis[N]={0};
stack<int> st;
int dsu[N];
ll dp[N], ans;

void dfs_topo(int u)
{
    vis[u]=1;
    for (auto v:g[u]) if (!vis[v]) dfs_topo(v);
    st.push(u);
}
void dfs_scc(int u, const int r)
{
    vis[u]=1; dsu[u]=r;
    val[r]+=a[u];
    for (auto v:rg[u]) if (!vis[v]) dfs_scc(v, r);
}
void dfs_dp(int u)
{
    vis[u]=1;
    for (auto v:g[u])
    {
        if (!vis[v]) dfs_dp(v);
        dp[u]=max(dp[u], dp[v]);
    }
    dp[u]+=val[u];
}

int main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>a[i];
    for (int i=0; i<m; i++)
    {
        cin>>x[i]>>y[i];
        g[x[i]].push_back(y[i]);
        rg[y[i]].push_back(x[i]);
    }
    
    for (int i=0; i<n; i++) if (!vis[i]) dfs_topo(i);
    for (int i=0; i<n; i++) vis[i]=0;
    while (st.size())
    {
        int u=st.top(); st.pop();
        if (!vis[u]) dfs_scc(u, u);
    }
    
    for (int i=0; i<n; i++) g[i].clear();
    for (int i=0; i<m; i++)
    {
        x[i]=dsu[x[i]]; y[i]=dsu[y[i]];
        if (x[i]!=y[i]) g[x[i]].push_back(y[i]);
    }
    
    for (int i=0; i<n; i++) vis[i]=0;
    for (int i=0; i<n; i++)
    {
        if (!vis[i]) dfs_dp(i);
        ans=max(ans, dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}