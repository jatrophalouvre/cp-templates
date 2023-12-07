// https://www.luogu.com.cn/problem/P4551
// livin' for the hope of it all

#include <iostream>
#include <cstring>
using namespace std;

const int N=100013, L=31;
int n, m;
int h[N], e[N<<1], ne[N<<1], idx=0;
int w[N<<1], d[N];

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
    for (int a=h[u]; ~a; a=ne[a])
    {
        int v=e[a];
        if (v==p) continue;
        d[v]=d[u]^w[a];
        dfs(v, u);
    }
}

int main()
{
    memset(h, -1, sizeof(h));
    trie=new node();
    cin>>n;
    for (int a=0; a<n-1; a++)
    {
        int x, y, z; cin>>x>>y>>z;
        e[idx]=y; w[idx]=z; ne[idx]=h[x]; h[x]=idx++;
        e[idx]=x; w[idx]=z; ne[idx]=h[y]; h[y]=idx++;
    }
    
    d[0]=0; dfs(0, 0);
    int ans=0;
    for (int a=0; a<n; a++) ans=max(ans, trie->query(d[a]));
    cout<<ans<<endl;
    return 0;
}