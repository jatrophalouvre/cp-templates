// https://www.luogu.com.cn/problem/P3379
// livin' for the hope of it all

#include <iostream>
#include <cstring>
using namespace std;

const int N=100013, L=22;
int n, m;
int h[N], e[N<<1], ne[N<<1], idx=0;

struct node
{
    int anc[N][L], dep[N];
    
    node()
    {
        memset(anc, -1, sizeof(anc));
        dep[0]=0; dfs(0, 0);
    }
    void dfs(int u, int p)
    {
        anc[u][0]=p;
        for (int a=1; a<L; a++) anc[u][a]=anc[anc[u][a-1]][a-1];
        
        for (int a=h[u]; ~a; a=ne[a])
        {
            int v=e[a];
            if (v!=p)
            {
                dep[v]=dep[u]+1;
                dfs(v, u);
            }
        }
    }
    int query(int x, int y)
    {
        if (dep[x]<dep[y]) swap(x, y);
        
        for (int a=L-1; a>=0; a--) if (dep[x]-(1<<a)>=dep[y]) x=anc[x][a];
        if (x==y) return x;
        
        for (int a=L-1; a>=0; a--) if (anc[x][a]!=anc[y][a])
        {
            x=anc[x][a];
            y=anc[y][a];
        }
        return anc[x][0];
    }
} *lca;

int main()
{
    memset(h, -1, sizeof(h));
    cin>>n>>m;
    for (int a=0; a<n-1; a++)
    {
        int x, y; cin>>x>>y;
        e[idx]=y; ne[idx]=h[x]; h[x]=idx++;
        e[idx]=x; ne[idx]=h[y]; h[y]=idx++;
    }
    
    lca=new node();
    while (m--)
    {
        int x, y; cin>>x>>y;
        cout<<lca->query(x, y)<<endl;
    }
    return 0;
}