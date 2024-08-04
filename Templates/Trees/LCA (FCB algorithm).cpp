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
        for (auto v:s[u]) if (v!=p)
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
    int f(int u, int v) { return dep[u]<dep[v]?u:v; }
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