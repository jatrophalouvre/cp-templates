// https://codeforces.com/problemset/problem/342/E
#include <iostream>
#include <vector>
using namespace std;
using ll=long long;

const int N=1000013, L=22;
int n, m;
vector<int> g[N];
int par[N];
ll dp[N];

struct LCA
{
    int st[N][L], lg[N];
    int pre[N], dep[N], idx=0;
    
    LCA()
    {
        dep[0]=0; dfs(0, 0);
        for (int i=2; i<=idx; i++) lg[i]=lg[i>>1]+1;
        for (int j=1; (1<<j)<=idx; j++)
        {
            for (int i=0; i+(1<<j)-1<idx; i++)
            {
                st[i][j]=f(st[i][j-1], st[i+(1<<(j-1))][j-1]);
            }
        }
    }
    void dfs(int u, int p)
    {
        st[idx][0]=u; pre[u]=idx++;
        for (auto v:g[u]) if (v!=p)
        {
            dep[v]=dep[u]+1;
            dfs(v, u);
            st[idx][0]=u; idx++;
        }
    }
    int query(int u, int v)
    {
        u=pre[u]; v=pre[v];
        if (u>v) swap(u, v);
        int i=lg[v-u+1];
        return f(st[u][i], st[v-(1<<i)+1][i]);
    }
    int dist(int u, int v)
    {
        int l=query(u, v);
        return dep[u]+dep[v]-2*dep[l];
    }
    int f(int u, int v) { return dep[u]<dep[v]?u:v; }
} *lca;
struct CD
{
    int sz[N];
    bool vis[N]={0};
    
    CD() { decomp(0, 0); }
    void decomp(int u, int p)
    {
        dfs_sz(u, u);
        int cur=dfs_get(u, u, sz[u]);
        vis[cur]=1;
        if (u==p) par[cur]=cur;
        else par[cur]=p;
        for (auto v:g[cur]) if (!vis[v]) decomp(v, cur);
    }
    void dfs_sz(int u, int p)
    {
        sz[u]=1;
        for (auto v:g[u]) if (v!=p)
        {
            if (vis[v]) continue;
            dfs_sz(v, u);
            sz[u]+=sz[v];
        }
    }
    int dfs_get(int u, int p, const int tsz)
    {
        for (auto v:g[u]) if (v!=p)
        {
            if (vis[v]) continue;
            if (sz[v]>tsz/2) return dfs_get(v, u, tsz);
        }
        return u;
    }
} *cd;

signed main()
{
    cin>>n>>m;
    for (int i=0; i<n-1; i++)
    {
        int u, v; cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    lca=new LCA();
    cd=new CD();
    for (int i=0; i<n; i++) dp[i]=1e18;
    dp[0]=0;
    int y=0;
    while (par[y]!=y)
    {
        y=par[y];
        dp[y]=min(dp[y], lca->dist(0, y));
    }
    
    while (m--)
    {
        int t, x; cin>>t>>x;
        if (t==1)
        {
            dp[x]=0;
            int y=x;
            while (par[y]!=y)
            {
                y=par[y];
                dp[y]=min(dp[y], lca->dist(x, y));
            }
        }
        else
        {
            int ans=dp[x];
            int y=x;
            while (par[y]!=y)
            {
                y=par[y];
                ans=min(ans, dp[y]+lca->dist(x, y));
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}