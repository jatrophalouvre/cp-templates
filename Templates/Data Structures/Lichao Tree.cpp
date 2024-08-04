// https://codebreaker.xyz/problem/convexhull
#include <iostream>
using namespace std;
using ll=long long;

const int N=1e9+13;
int n;

struct line
{
    ll a=0, b=-1e18;
    ll operator()(ll x) { return a*x+b; }
    bool operator==(line x) { return a==x.a && b==x.b; }
};
struct LCT
{
    int l, r, mid;
    line v;
    LCT *lptr, *rptr;
    
    LCT(int L, int R)
    {
        l=L; r=R; mid=(l+r)>>1;
        lptr=rptr=nullptr;
    }
    void build()
    {
        if (lptr==nullptr) lptr=new LCT(l, mid);
        if (rptr==nullptr) rptr=new LCT(mid+1, r);
    }
    void ins(line x)
    {
        bool bl=(x(l)>v(l)), bm=(x(mid)>v(mid)), br=(x(r)>v(r));
        if (bm) swap(x, v);
        if (l==r || x==v || bl==br) return;
        build();
        if (bl!=bm) lptr->ins(x);
        else rptr->ins(x);
    }
    ll qry(ll x)
    {
        if (l==r || lptr==nullptr) return v(x);
        build();
        if (x<=mid) return max(v(x), lptr->qry(x));
        else return max(v(x), rptr->qry(x));
    }
} *lct;

int main()
{
    lct=new LCT(-N, N);
    cin>>n;
    while (n--)
    {
        int t; cin>>t;
        if (t==1)
        {
            ll a, b; cin>>a>>b;
            lct->ins({a, b});
        }
        else
        {
            ll x; cin>>x;
            cout<<lct->qry(x)<<endl;
        }
    }
    return 0;
}