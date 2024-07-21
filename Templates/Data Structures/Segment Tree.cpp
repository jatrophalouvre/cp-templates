// https://www.luogu.com.cn/problem/P3372
#include <iostream>
using namespace std;
using ll=long long;

const int N=100013;
int n, m;
ll s[N];

struct SEG
{
    int l, r, mid;
    ll v, lz;
    SEG *lptr, *rptr;
    
    SEG(int L, int R)
    {
        l=L; r=R; mid=(l+r)>>1;
        lz=0;
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
    void upd(int pos, ll val)
    {
        if (l==r)
        {
            v=val;
            return;
        }
        prop();
        if (pos<=mid) lptr->upd(pos, val);
        else rptr->upd(pos, val);
        v=lptr->v+rptr->v;
    }
    void upd(int x, int y, ll val)
    {
        if (l==x && r==y)
        {
            v+=val*(r-l+1);
            lz+=val;
            return;
        }
        prop();
        if (y<=mid) lptr->upd(x, y, val);
        else if (x>mid) rptr->upd(x, y, val);
        else
        {
            lptr->upd(x, mid, val);
            rptr->upd(mid+1, y, val);
        }
        v=lptr->v+rptr->v;
    }
    ll qry(int pos)
    {
        if (l==r) return v;
        prop();
        if (pos<=mid) return lptr->qry(pos);
        else return rptr->qry(pos);
    }
    ll qry(int x, int y)
    {
        if (l==x && r==y) return v;
        prop();
        if (y<=mid) return lptr->qry(x, y);
        else if (x>mid) return rptr->qry(x, y);
        else return lptr->qry(x, mid)+rptr->qry(mid+1, y);
    }
    void prop()
    {
        if (lz==0) return;
        lptr->v+=lz*(mid-l+1);
        lptr->lz+=lz;
        rptr->v+=lz*(r-mid);
        rptr->lz+=lz;
        lz=0;
    }
} *seg;

int main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>s[i];
    
    seg=new SEG(0, n-1);
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int l, r; ll val; cin>>l>>r>>val;
            seg->upd(l, r, val);
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<seg->qry(l, r)<<endl;
        }
    }
    return 0;
}