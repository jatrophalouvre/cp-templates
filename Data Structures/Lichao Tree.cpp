// https://codebreaker.xyz/problem/convexhull
// to be reviewed

#include <iostream>
using namespace std;

using ll = long long;
const int N=1e9+13;
int n;

struct line
{
    ll m, b;
    
    line() { m=0; b=-1e18; }
    line(ll _m, ll _b) { m=_m; b=_b; }
    ll operator()(ll x) { return m*x+b; }
};
struct node
{
    int l, r, mid; line v;
    node *lptr, *rptr;
    
    node(int _l, int _r)
    {
        l=_l; r=_r;
        mid=(l+r)>>1;
        lptr=rptr=nullptr;
    }
    void build()
    {
        if (lptr==nullptr) lptr=new node(l, mid);
        if (rptr==nullptr) rptr=new node(mid+1, r);
    }
    void update(line x)
    {
        bool bl=(x(l)>v(l)), bm=(x(mid)>v(mid));
        if (bm) swap(x, v);
        if (l==r) return;
        build();
        if (bl==bm) rptr->update(x);
        else lptr->update(x);
    }
    ll query(ll x)
    {
        if (l==r) return v(x);
        ll ans=v(x);
        build();
        if (x<=mid) ans=max(ans, lptr->query(x));
        else ans=max(ans, rptr->query(x));
        return ans;
    }
} *lctree;

int main()
{
    lctree=new node(-N, N);
    cin>>n;
    while (n--)
    {
        int t; cin>>t;
        if (t==1)
        {
            ll m, b; cin>>m>>b;
            lctree->update(line(m, b));
        }
        else
        {
            ll x; cin>>x;
            cout<<lctree->query(x)<<endl;
        }
    }
    return 0;
}