// https://codebreaker.xyz/problem/convexhull
// to be reviewed

#include <iostream>
using namespace std;

using ll = long long;
const int N=1e9+13;
int n;

struct line
{
    ll m=0, b=-1e18;
    ll operator()(ll x) { return m*x+b; }
};
struct node
{
    int l, r, mid;
    line v;
    node *lptr, *rptr;
    
    node(int L, int R)
    {
        l=L; r=R;
        mid=(l+r)>>1;
        lptr=rptr=nullptr;
    }
    void build()
    {
        if (lptr==nullptr) lptr=new node(l, mid);
        if (rptr==nullptr) rptr=new node(mid+1, r);
    }
    void insert(line x)
    {
        bool bl=(x(l)>v(l)), bm=(x(mid)>v(mid));
        if (bm) swap(x, v);
        if (l==r) return;
        build();
        if (bl==bm) rptr->insert(x);
        else lptr->insert(x);
    }
    ll query(ll x)
    {
        if (l==r) return v(x);
        build();
        ll ans=v(x);
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
            lctree->insert({m, b});
        }
        else
        {
            ll x; cin>>x;
            cout<<lctree->query(x)<<endl;
        }
    }
    return 0;
}