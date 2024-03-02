// https://www.luogu.com.cn/problem/P3387
#include <iostream>
#include <stack>
#include <vector>
#define int long long
using namespace std;

const int N=100013, M=5000013;
int n, m;
int x[M], y[M];
vector<int> s[N], rs[N];
int a[N], val[N]={0};
bool vis[N]={0};
stack<int> st;
int g[N];
int dp[N], ans;

void dfs_topo(int u)
{
    vis[u]=1;
    for (auto v:s[u]) if (!vis[v]) dfs_topo(v);
    st.push(u);
}
void dfs_scc(int u, int r)
{
    vis[u]=1; g[u]=r;
    val[r]+=a[u];
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

signed main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>a[i];
    for (int i=0; i<m; i++)
    {
        cin>>x[i]>>y[i];
        s[x[i]].push_back(y[i]);
        rs[y[i]].push_back(x[i]);
    }
    
    for (int i=0; i<n; i++) if (!vis[i]) dfs_topo(i);
	fill(vis, vis+n, 0);
    while (st.size())
    {
        int u=st.top(); st.pop();
        if (!vis[u]) dfs_scc(u, u);
    }
    
    for (int i=0; i<n; i++) s[i].clear();
    for (int i=0; i<m; i++)
    {
        if (g[x[i]]!=g[y[i]])
        {
            x[i]=g[x[i]]; y[i]=g[y[i]];
            s[x[i]].push_back(y[i]);
        }
    }
    
	fill(vis, vis+n, 0);
    for (int i=0; i<n; i++)
    {
        if (!vis[i]) dfs_dp(i);
        ans=max(ans, dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}