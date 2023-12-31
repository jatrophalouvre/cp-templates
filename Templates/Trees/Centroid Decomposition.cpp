// https://codebreaker.xyz/problem/gwynethandtree
// to be reviewed

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=100013, M=200013, L=23;
int n, m;
vector<int> s[N];
int d[N][L], ans[N];
int c[N][L], lvl[N];

struct node
{
    int sz[N];
    
    node()
    {
        memset(c, -1, sizeof(c));
        memset(lvl, -1, sizeof(lvl));
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
		for (auto v:s[u])
        {
            if (v==p || lvl[v]!=-1) continue;
            if (tsz<sz[v]*2)
            {
                return get(v, u, tsz);
            }
        }
        return u;
    }
    void dfs_sz(int u, int p)
    {
        sz[u]=1;
        for (auto v:s[u])
        {
            if (v==p || lvl[v]!=-1) continue;
            dfs_sz(v, u);
            sz[u]+=sz[v];
        }
    }
    void dfs_c(int u, int p, const int level, const int cent, int dep)
    {
        c[u][level]=cent; d[u][level]=dep;
        for (auto v:s[u])
        {
            if (v==p || lvl[v]!=-1) continue;
            dfs_c(v, u, level, cent, dep+1);
        }
    }
} *centd;

signed main()
{
    cin>>n>>m;
    for (int a=0; a<n-1; a++)
    {
        int x, y; cin>>x>>y;
        s[x].push_back(y);
        s[y].push_back(x);
    }
    
    centd=new node();
    for (int a=0; a<n; a++) ans[a]=1e9;
    for (int a=0; a<=lvl[0]; a++) ans[c[0][a]]=min(ans[c[0][a]], d[0][a]);
    while (m--)
    {
        int t, x; cin>>t>>x;
        if (t==1)
        {
            for (int a=0; a<=lvl[x]; a++)
            {
                ans[c[x][a]]=min(ans[c[x][a]], d[x][a]);
            }
        }
        else
        {
            int dist=1e9;
            for (int a=0; a<=lvl[x]; a++) dist=min(dist, ans[c[x][a]]+d[x][a]);
            cout<<dist<<endl;
        }
    }
    return 0;
}
