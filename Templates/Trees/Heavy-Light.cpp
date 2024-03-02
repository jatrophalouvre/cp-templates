// https://www.luogu.com.cn/problem/P3384
#include <iostream>
#include <vector>
#define int long long
using namespace std;

const int N=100013;
int n, m;
vector<int> s[N];
int a[N];
int seq[N], pre[N], post[N], idx=0;

struct SEG
{
	int l, r, mid;
    int v, lazy;
    SEG *lptr, *rptr;
    
    SEG(int L, int R)
    {
        l=L; r=R; mid=(l+r)>>1;
        lazy=0;
        if (l==r)
        {
            lptr=rptr=nullptr;
            v=a[seq[l]];
        }
        else
        {
            lptr=new SEG(l, mid);
            rptr=new SEG(mid+1, r);
            v=lptr->v+rptr->v;
        }
    }
    void update(int x, int y, int a)
    {
        if (l==x && r==y)
        {
            lazy+=a;
            v+=a*(r-l+1);
            return;
        }
        prop();
        if (y<=mid) lptr->update(x, y, a);
        else if (x>=mid+1) rptr->update(x, y, a);
        else
        {
            lptr->update(x, mid, a);
            rptr->update(mid+1, y, a);
        }
        v=lptr->v+rptr->v;
    }
    int query(int x, int y)
    {
        if (x==l && r==y) return v;
        prop();
        if (y<=mid) return lptr->query(x, y);
        else if (x>=mid+1) return rptr->query(x, y);
        else return lptr->query(x, mid) + rptr->query(mid+1, y);
    }
    void prop()
    {
        if (lazy==0) return;
        lptr->lazy+=lazy;
        rptr->lazy+=lazy;
        lptr->v+=lazy*(mid-l+1);
        rptr->v+=lazy*(r-mid);
        lazy=0;
    }
} *seg;
struct HLD
{
    int dep[N], p[N], sz[N];
    int heavy[N], head[N];
    
    HLD()
    {
        fill(heavy, heavy+n, -1);
        dfs_sz(0);
        dfs_hl(0, 0);
    }
    void dfs_sz(int u)
    {
        sz[u]=1;
        for (auto v:s[u]) if (v!=p[u])
        {
            dep[v]=dep[u]+1; p[v]=u;
            dfs_sz(v);
            if (heavy[u]==-1 || sz[heavy[u]]<sz[v]) heavy[u]=v;
            sz[u]+=sz[v];
        }
    }
    void dfs_hl(int u, int H)
    {
        seq[idx]=u; pre[u]=idx++;
        head[u]=H;
        if (heavy[u]!=-1) dfs_hl(heavy[u], H);
        for (auto v:s[u]) if (v!=p[u] && v!=heavy[u]) dfs_hl(v, v);
        post[u]=idx-1;
    }
    void update(int x, int y, int val)
    {
        int fx=head[x], fy=head[y];
        while (fx!=fy)
        {
            if (dep[fx]<dep[fy])
            {
                swap(x, y);
                swap(fx, fy);
            }
            seg->update(pre[fx], pre[x], val);
            x=p[fx]; fx=head[x];
        }
        if (dep[x]>dep[y]) swap(x, y);
        seg->update(pre[x], pre[y], val);
    }
    int query(int x, int y)
    {
        int fx=head[x], fy=head[y]; int ans=0;
        while (fx!=fy)
        {
            if (dep[fx]<dep[fy])
            {
                swap(x, y);
                swap(fx, fy);
            }
            ans += seg->query(pre[fx], pre[x]);
            x=p[fx]; fx=head[x];
        }
        if (dep[x]>dep[y]) swap(x, y);
        return ans + seg->query(pre[x], pre[y]);
    }
} *hld;

signed main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>a[i];
    for (int i=0; i<n-1; i++)
    {
        int u, v; cin>>u>>v;
        s[u].push_back(v);
        s[v].push_back(u);
    }
    
    hld=new HLD();
    seg=new SEG(0, n-1);
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int x, y, a; cin>>x>>y>>a;
            hld->update(x, y, a);
        }
        else if (t==2)
        {
            int x, y; cin>>x>>y;
            cout<<hld->query(x, y)<<endl;
        }
        else if (t==3)
        {
            int x, a; cin>>x>>a;
            seg->update(pre[x], post[x], a);
        }
        else
        {
            int x; cin>>x;
            cout<<seg->query(pre[x], post[x])<<endl;
        }
    }
    return 0;
}