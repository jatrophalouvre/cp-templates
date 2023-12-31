// https://www.luogu.com.cn/problem/P3372
// livin' for the hope of it all

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=100013;
int n, m;
int s[N];

struct node
{
    int l, r, mid;
    int v, lazy;
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
            v=lptr->v+rptr->v;
        }
    }
    void update(int pos, int val)
    {
        if (l==r)
        {
            assert(l==pos);
            v=val;
            return;
        }
        prop();
        if (pos<=mid) lptr->update(pos, val);
        else rptr->update(pos, val);
        v=lptr->v+rptr->v;
    }
    void update(int x, int y, int val)
    {
        if (l==x && r==y)
        {
            v+=val*(r-l+1);
            lazy+=val;
            return;
        }
        prop();
        if (y<=mid) lptr->update(x, y, val);
        else if (x>=mid+1) rptr->update(x, y, val);
        else
        {
            lptr->update(x, mid, val);
            rptr->update(mid+1, y, val);
        }
        v=lptr->v+rptr->v;
    }
    int query(int pos)
    {
        if (l==r)
        {
            assert(l==pos);
            return v;
        }
        prop();
        if (pos<=mid) return lptr->query(pos);
        else return rptr->query(pos);
    }
    int query(int x, int y)
    {
        if (l==x && r==y) return v;
        prop();
        if (y<=mid) return lptr->query(x, y);
        else if (x>=mid+1) return rptr->query(x, y);
        else return lptr->query(x, mid)+rptr->query(mid+1, y);
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
} *segtree;

signed main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++) cin>>s[a];
    
    segtree=new node(0, n-1);    
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int x, y, val; cin>>x>>y>>val;
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