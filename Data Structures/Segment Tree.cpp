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
#define lv lptr->v
#define rv rptr->v
#define llazy lptr->lazy
#define rlazy rptr->lazy
    
    int l, r, mid;
    ll v, lazy;
    node *lptr, *rptr;
    
    node(int L, int R)
    {
        l=L; r=R; mid=(l+r)>>1;
        lazy=0;
        if (l==r)
        {
            lptr=rptr=nullptr;
            v=s[l];
        }
        else
        {
            lptr=new node(l, mid);
            rptr=new node(mid+1, r);
            v=lv+rv;
        }
    }
    void update(int pos, ll val)
    {
        if (l==r)
        {
            assert(l==pos);
            v=val;
            return;
        }
        pushdown();
        if (pos<=mid) lptr->update(pos, val);
        else rptr->update(pos, val);
        v=lv+rv;
    }
    void update(int x, int y, ll val)
    {
        if (x==l && r==y)
        {
            lazy+=val;
            v+=val*(r-l+1);
            return;
        }
        pushdown();
        if (y<=mid) lptr->update(x, y, val);
        else if (x>=mid+1) rptr->update(x, y, val);
        else
        {
            lptr->update(x, mid, val);
            rptr->update(mid+1, y, val);
        }
        v=lv+rv;
    }
    ll query(int pos)
    {
        if (l==r)
        {
            assert(l==pos);
            return v;
        }
        pushdown();
        if (pos<=mid) return lptr->query(pos);
        else return rptr->query(pos);
    }
    ll query(int x, int y)
    {
        if (l==x && y==r) return v;
        pushdown();
        if (y<=mid) return lptr->query(x, y);
        else if (x>=mid+1) return rptr->query(x, y);
        else return lptr->query(x, mid) + rptr->query(mid+1, y);
    }
    void pushdown()
    {
        if (lazy==0) return;
        llazy+=lazy;
        lv+=lazy*(mid-l+1);
        rlazy+=lazy;
        rv+=lazy*(r-mid);
        lazy=0;
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
            segtree->update(x, y, val);
        }
        else
        {
            int x, y; cin>>x>>y;
            cout<<segtree->query(x, y)<<endl;
        }
    }
    return 0;
}