// https://codebreaker.xyz/problem/convexhull
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
using ll=long long;
using ld=long double;

int n;

struct line
{
    ll a=0, b=-1e18;
    ll operator()(ll x) { return a*x+b; }
};
struct CHT
{
    deque<line> q;
    
    CHT() {}
    void ins(line x)
    {
        while (q.size()>=2 && sect(x, q[q.size()-2])>=sect(x, q[q.size()-1])) q.pop_back();
        q.push_back(x);
    }
    ll qry(ll x)
    {
        if (q.size()==1) return q[0](x);
        if (sect(q[0], q[1])>ld(x)) return q[0](x);
        int l=1, r=q.size();
        while (l+1<r)
        {
            int mid=(l+r)>>1;
            if (sect(q[mid-1], q[mid])<=ld(x)) l=mid;
            else r=mid;
        }
		return q[l](x);
    }
    ld sect(line x, line y)
    {
        if (x.a==y.a) return -1e18;
        else return ld(x.b-y.b)/ld(y.a-x.a);
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
            cht->ins({a, b});
        }
        else
        {
            ll x; cin>>x;
            cout<<cht->qry(x)<<endl;
        }
    }
    return 0;
}