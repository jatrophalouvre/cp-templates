// https://codebreaker.xyz/problem/gwynethandtree
// to be reviewed

#include <iostream>
#include <vector>
#define int long long
using namespace std;

const int N=100013, L=22;
int n, m;
vector<int> s[N];
int d[N][L], ans[N];
int c[N][L], lvl[N];

struct CD
{
    int sz[N];
    
    CD()
    {
        for (int i=0; i<n; i++) fill(c[i], c[i]+L, -1);
        fill(lvl, lvl+n, -1);
        decomp(0, 0, 0);
    }
    void decomp(int u, int p, int dep)
    {
        dfs_sz(u, u);
        int cent=get(u, u, sz[u]);
        lvl[cent]=dep;
        dfs_c(cent, cent, dep, cent, 0);
        for (auto v:s[cent]) if (lvl[v]==-1) decomp(v, cent, dep+1);
    }
    int get(int u, int p, const int tsz)
    {
		for (auto v:s[u]) if (v!=p)
        {
            if (lvl[v]!=-1) continue;
            if (tsz<sz[v]*2) return get(v, u, tsz);
        }
        return u;
    }
    void dfs_sz(int u, int p)
    {
        sz[u]=1;
        for (auto v:s[u]) if (v!=p)
        {
            if (lvl[v]!=-1) continue;
            dfs_sz(v, u);
            sz[u]+=sz[v];
        }
    }
    void dfs_c(int u, int p, const int level, const int cent, int dep)
    {
        c[u][level]=cent; d[u][level]=dep;
        for (auto v:s[u]) if (v!=p)
        {
            if (lvl[v]!=-1) continue;
            dfs_c(v, u, level, cent, dep+1);
        }
    }
} *cd;

signed main()
{
    cin>>n>>m;
    for (int i=0; i<n-1; i++)
    {
        int x, y; cin>>x>>y;
        s[x].push_back(y);
        s[y].push_back(x);
    }
    
    cd=new CD();
    for (int i=0; i<n; i++) ans[i]=1e18;
    for (int i=0; i<=lvl[0]; i++) ans[c[0][i]]=min(ans[c[0][i]], d[0][i]);
    while (m--)
    {
        int t, x; cin>>t>>x;
        if (t==1)
        {
            for (int i=0; i<=lvl[x]; i++)
            {
                ans[c[x][i]]=min(ans[c[x][i]], d[x][i]);
            }
        }
        else
        {
            int dist=1e9;
            for (int i=0; i<=lvl[x]; i++) dist=min(dist, ans[c[x][i]]+d[x][i]);
            cout<<dist<<endl;
        }
    }
    return 0;
}