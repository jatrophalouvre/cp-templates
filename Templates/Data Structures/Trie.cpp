// https://www.luogu.com.cn/problem/P4551
// livin' for the hope of it all

#include <bits/stdc++.h>
#define int long long
#define fir first
#define sec second
using namespace std;

using PII = pair<int, int>;
const int N=100013, L=26;
int n, m;
vector<PII> s[N];
int d[N];

struct node
{
    int ne[N][3], idx=1;
    bool e[N]={0};
    
    node() { memset(ne, -1, sizeof(ne)); }
    void insert(int x)
    {
        int p=0;
        for (int a=L; a>=0; a--)
        {
            int u=(x>>a)&1;
            if (ne[p][u]==-1) ne[p][u]=idx++;
            p=ne[p][u];
        }
        e[p]=1;
    }
    int query(int x)
    {
        int p=0, ans=0;
        for (int a=L; a>=0; a--)
        {
            int u=(x>>a)&1;
            if (ne[p][!u]!=-1)
            {
                ans+=(1<<a);
                p=ne[p][!u];
            }
            else p=ne[p][u];
        }
        return ans;
    }
} *trie;
void dfs(int u, int p)
{
    trie->insert(d[u]);
    for (auto [v, w]:s[u])
    {
        if (v==p) continue;
        d[v]=d[u]^w;
        dfs(v, u);
    }
}

signed main()
{
    trie=new node();
    cin>>n;
    for (int a=0; a<n-1; a++)
    {
        int x, y, z; cin>>x>>y>>z;
        s[x].push_back({y, z});
        s[y].push_back({x, z});
    }
    
    d[0]=0; dfs(0, 0);
    int ans=0;
    for (int a=0; a<n; a++) ans=max(ans, trie->query(d[a]));
    cout<<ans<<endl;
    return 0;
}