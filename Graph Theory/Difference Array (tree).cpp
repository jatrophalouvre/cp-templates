// https://www.luogu.com.cn/problem/P3258
// livin' for the hope of it all

#include <iostream>
#include <cstring>
using namespace std;

const int N=100013, L=22;
int n;
int h[N], e[N<<1], ne[N<<1], idx=0;
int p[N], ord[N], s[N]={0};

struct node
{
    int st[N][L], lg[N];
    int pre[N], dep[N], i=0;
    
    node()
    {
        memset(pre, -1, sizeof(pre));
        dep[0]=p[0]=0; dfs(0);
        for (int a=2; a<=i; a++) lg[a]=lg[a>>1]+1;
        for (int b=1; (1<<b)<i; b++)
        {
            for (int a=0; a+(1<<b)-1<i; a++)
            {
                st[a][b]=f(st[a][b-1], st[a+(1<<(b-1))][b-1]);
            }
        }
    }
    void dfs(int u)
    {
        st[i][0]=u; pre[u]=i++;
        for (int a=h[u]; ~a; a=ne[a])
        {
            int v=e[a];
            if (pre[v]==-1)
            {
                dep[v]=dep[u]+1;
                p[v]=u;
                dfs(v);
                st[i][0]=u; i++;
            }
        }
    }
    int query(int x, int y)
    {
        x=pre[x]; y=pre[y];
        if (x>y) swap(x, y);
        int t=lg[y-x+1];
        return f(st[x][t], st[y-(1<<t)+1][t]);
    }
    int f(int x, int y) { return dep[x]<dep[y]?x:y; }
} *lca;
void calc(int u, int p)
{
    for (int a=h[u]; ~a; a=ne[a])
    {
        int v=e[a];
        if (v==p) continue;
        calc(v, u);
        s[u]+=s[v];
    }
}

int main()
{
    memset(h, -1, sizeof(h));
    cin>>n;
    for (int a=0; a<n; a++) cin>>ord[a];
    for (int a=0; a<n-1; a++)
    {
        int x, y; cin>>x>>y;
        e[idx]=y; ne[idx]=h[x]; h[x]=idx++;
        e[idx]=x; ne[idx]=h[y]; h[y]=idx++;
    }
    
    lca=new node();
    p[0]=n;
    for (int a=0; a<n-1; a++)
    {
        int l=lca->query(ord[a], ord[a+1]);
        s[p[l]]--; s[l]--;
        s[ord[a]]++; s[ord[a+1]]++;
    }
    calc(0, 0);
    for (int a=1; a<n; a++) s[ord[a]]--;
    for (int a=0; a<n; a++) cout<<s[a]<<endl;
    return 0;
}