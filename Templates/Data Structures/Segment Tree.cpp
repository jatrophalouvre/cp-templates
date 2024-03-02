// https://www.luogu.com.cn/problem/P3372
#include <iostream>
#define int long long
using namespace std;

const int N=100013;
int n, m;
int s[N];

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
            v=s[l];
        }
        else
        {
            lptr=new SEG(l, mid);
            rptr=new SEG(mid+1, r);
            v=lptr->v+rptr->v;
        }
    }
    void update(int pos, int val)
    {
        if (l==r)
        {
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
        if (l==r) return v;
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
        lptr->v+=lazy*(mid-l+1);
        lptr->lazy+=lazy;
        rptr->v+=lazy*(r-mid);
        rptr->lazy+=lazy;
        lazy=0;
    }
} *seg;

signed main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>s[i];
    
    seg=new SEG(0, n-1);
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int l, r, val; cin>>l>>r>>val;
            seg->update(l, r, val);
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<seg->query(l, r)<<endl;
        }
    }
    return 0;
}