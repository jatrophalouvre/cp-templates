// https://www.luogu.com.cn/problem/P3372
#include <iostream>
using namespace std;
using ll=long long;

const int N=100013;
int n, m;
ll a[N];

struct SEG
{
    int st, te, mid;
    ll v, lz;
    SEG *lp, *rp;
    
    SEG(int L, int R)
    {
        st=L; te=R; mid=(st+te)/2;
        lz=0;
        if (st==te)
        {
            lp=rp=nullptr;
            v=a[st];
        }
        else
        {
            lp=new SEG(st, mid);
            rp=new SEG(mid+1, te);
            v=lp->v+rp->v;
        }
    }
    void upd(int p, ll z)
    {
        if (st==te)
        {
            v=z;
            return;
        }
        prop();
        if (p<=mid) lp->upd(p, z);
        else rp->upd(p, z);
        v=lp->v+rp->v;
    }
    void upd(int l, int r, ll z)
    {
        if (l==st && r==te)
        {
            v+=z*(r-l+1);
            lz+=z;
            return;
        }
        prop();
        if (r<=mid) lp->upd(l, r, z);
        else if (l>mid) rp->upd(l, r, z);
        else
        {
            lp->upd(l, mid, z);
            rp->upd(mid+1, r, z);
        }
        v=lp->v+rp->v;
    }
    ll qry(int p)
    {
        if (st==te) return v;
        prop();
        if (p<=mid) return lp->qry(p);
        else return rp->qry(p);
    }
    ll qry(int l, int r)
    {
        if (l==st && r==te) return v;
        prop();
        if (r<=mid) return lp->qry(l, r);
        else if (l>mid) return rp->qry(l, r);
        else return lp->qry(l, mid)+rp->qry(mid+1, r);
    }
    void prop()
    {
        if (lz==0) return;
        lp->v+=lz*(mid-st+1);
        lp->lz+=lz;
        rp->v+=lz*(te-mid);
        rp->lz+=lz;
        lz=0;
    }
} *seg;

int main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>a[i];
    
    seg=new SEG(0, n-1);
    while (m--)
    {
        int t, l, r; cin>>t>>l>>r;
        if (t==1)
        {
            ll z; cin>>z;
            seg->upd(l, r, z);
        }
        else cout<<seg->qry(l, r)<<endl;
    }
    return 0;
}