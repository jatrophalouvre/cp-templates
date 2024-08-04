// https://www.luogu.com.cn/problem/P3379
#include <iostream>
#include <vector>
#define int long long
using namespace std;

const int N=100013, L=22;
int n, m;
vector<int> s[N];

struct LCA
{
    int pre[N], post[N], idx=0;
    int anc[N][L], dep[N];
    
    LCA()
    {
        for (int i=0; i<n; i++) fill(anc[i], anc[i]+L, -1);
        dep[0]=0; dfs(0, 0);
    }
    void dfs(int u, int p)
    {
        pre[u]=idx++;
        anc[u][0]=p;
        for (int i=1; i<L; i++)
        {
            anc[u][i]=anc[anc[u][i-1]][i-1];
            if (anc[u][i]==-1) break;
        }
        for (auto v:s[u]) if (v!=p)
        {
            dep[v]=dep[u]+1;
            dfs(v, u);
        }
        post[u]=idx-1;
    }
    bool check(int u, int v) { return pre[u]<=pre[v] && post[u]>=post[v]; }
    int query(int u, int v)
    {
        if (check(u, v)) return u;
        if (check(v, u)) return v;
        if (dep[u]>dep[v]) swap(u, v);
        for (int i=L-1; i>=0; i--) if (anc[u][i]!=-1 && !check(anc[u][i], v)) u=anc[u][i];
        return anc[u][0];
    }
} *lca;

signed main()
{
    cin>>n>>m;
    for (int i=0; i<n-1; i++)
    {
        int u, v; cin>>u>>v;
        s[u].push_back(v);
        s[v].push_back(u);
    }
    
    lca=new LCA();
    while (m--)
    {
        int u, v; cin>>u>>v;
        cout<<lca->query(u, v)<<endl;
    }
    return 0;
}