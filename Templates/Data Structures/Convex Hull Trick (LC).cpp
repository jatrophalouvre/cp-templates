// https://codebreaker.xyz/problem/convexhull
// to be reviewed
#include <iostream>
#include <set>
using namespace std;
using ll=long long;

int n;

struct line
{
    mutable ll a, b, p;
    ll operator()(ll x) { return a*x+b; }
    bool operator<(line x) const { return a<x.a; }
    bool operator<(ll x) const { return p<x; }
};
struct CHT:multiset<line, less<>>
{
    CHT() {}
    void add(line l)
    {
        auto z=insert(l);
        auto y=z++, x=y;
        while (sect(y, z)) z=erase(z);
        if (x!=begin() && sect(--x, y)) sect(x, y=erase(y));
        while ((y=x)!=begin() && ((--x)->p)>=(y->p)) sect(x, erase(y));
    }
    ll qry(ll x)
    {
        auto l=*lower_bound(x);
        return ll(l(x));
    }
    ll div(ll x, ll y) { return x/y-((x^y)<0 && x%y); }
    bool sect(iterator x, iterator y)
    {
        if (y==end()) return x->p=1e18, 0;
        if (x->a==y->a) x->p=(x->b)>(y->b)?1e18:-1e18;
        else x->p=div((y->b)-(x->b), (x->a)-(y->a));
        return (x->p)>=(y->p);
    }
} *cht;

int main()
{
    cht=new CHT();
    cin>>n;
    while (n--)
    {
        int t; cin>>t;
        if (t==1)
        {
            ll a, b; cin>>a>>b;
            cht->add({a, b, 0});
        }
        else
        {
            ll x; cin>>x;
            cout<<cht->qry(x)<<endl;
        }
    }
    return 0;
}