// https://codebreaker.xyz/problem/convexhull
// to be reviewed
#include <iostream>
#include <set>
#define int long long
#define double long double
using namespace std;

int n;

struct line
{
    mutable int a, b, p;
    int operator()(int x) { return a*x+b; }
    bool operator<(line x) const { return a<x.a; }
    bool operator<(int x) const { return p<x; }
};
struct CHT:multiset<line, less<>>
{
    CHT() {}
    void add(line l)
    {
        auto z=insert(l);
        auto y=z++, x=y;
        while (isect(y, z)) z=erase(z);
        if (x!=begin() && isect(--x, y)) isect(x, y=erase(y));
        while ((y=x)!=begin() && ((--x)->p)>=(y->p)) isect(x, erase(y));
    }
    int query(int x)
    {
        auto l=*lower_bound(x);
        return (int)l(x);
    }
    int div(int x, int y) { return x/y-((x^y)<0 && x%y); }
    bool isect(iterator x, iterator y)
    {
        if (y==end()) return x->p=1e18, 0;
        if (x->a==y->a) x->p=(x->b)>(y->b)?1e18:-1e18;
        else x->p=div((y->b)-(x->b), (x->a)-(y->a));
        return (x->p)>=(y->p);
    }
} *cht;

signed main()
{
    cht=new CHT();
    cin>>n;
    while (n--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int a, b; cin>>a>>b;
            cht->add({a, b, 0});
        }
        else
        {
            int x; cin>>x;
            cout<<cht->query(x)<<endl;
        }
    }
    return 0;
}