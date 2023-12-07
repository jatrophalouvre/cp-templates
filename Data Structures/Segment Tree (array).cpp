// https://www.luogu.com.cn/problem/P3372
// livin' for the hope of it all

#include <iostream>
#include <cassert>
using namespace std;

using ll = long long;
const int N=100013;
int n, m;
ll s[N];

struct node
{
#define lt u*2
#define rt u*2+1
#define l L[u]
#define r R[u]
#define mid M[u]
    
    int L[N<<2], R[N<<2], M[N<<2];
    ll v[N<<2], lazy[N<<2];
    
    node(int LL, int RR) { build(1, LL, RR); }
    void build(int u, int LL, int RR)
    {
        L[u]=LL; R[u]=RR; M[u]=(LL+RR)>>1;
        lazy[u]=0;
        if (l==r) v[u]=s[l];
        else
        {
            build(lt, l, mid);
            build(rt, mid+1, r);
            v[u]=v[lt]+v[rt];
        }
    }
    void update(int u, int pos, ll val)
    {
        if (l==r)
        {
            assert(l==pos);
            v[u]=val;
            return;
        }
        pushdown(u);
        if (pos<=mid) update(lt, pos, val);
        else update(rt, pos, val);
        v[u]=v[lt]+v[rt];
    }
    void update(int u, int x, int y, ll val)
    {
        if (x==l && r==y)
        {
            v[u]+=val*(r-l+1);
            lazy[u]+=val;
            return;
        }
        pushdown(u);
        if (y<=mid) update(lt, x, y, val);
        else if (x>=mid+1) update(rt, x, y, val);
        else
        {
            update(lt, x, mid, val);
            update(rt, mid+1, y, val);
        }
        v[u]=v[lt]+v[rt];
    }
    ll query(int u, int pos)
    {
        if (l==r)
        {
            assert(l==pos);
            return v[u];
        }
        pushdown(u);
        if (pos<=mid) return query(lt, pos);
        else return query(rt, pos);
    }
    ll query(int u, int x, int y)
    {
        if (l==x && y==r) return v[u];
        pushdown(u);
        if (y<=mid) return query(lt, x, y);
        else if (x>=mid+1) return query(rt, x, y);
        else return query(lt, x, mid) + query(rt, mid+1, y);
    }
    void pushdown(int u)
    {
        if (lazy[u]==0) return;
        lazy[lt]+=lazy[u];
        lazy[rt]+=lazy[u];
        v[lt]+=lazy[u]*(mid-l+1);
        v[rt]+=lazy[u]*(r-mid);
        lazy[u]=0;
    }
} *segtree;

int main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++) cin>>s[a];
    segtree=new node(0, n-1);
    
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int x, y; ll val; cin>>x>>y>>val;
            segtree->update(1, x, y, val);
        }
        else
        {
            int x, y; cin>>x>>y;
            cout<<segtree->query(1, x, y)<<endl;
        }
    }
    return 0;
}