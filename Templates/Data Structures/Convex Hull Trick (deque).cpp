// https://codebreaker.xyz/problem/convexhull
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define int long long
#define double long double
using namespace std;

int n;

struct line
{
    int a=0, b=-1e18;
    int operator()(int x) { return a*x+b; }
};
struct CHT
{
    deque<line> q;
    
    CHT() {}
    void insert(line x)
    {
        while (q.size()>=2 && intersect(x, q[q.size()-2])>=intersect(x, q[q.size()-1])) q.pop_back();
        q.push_back(x);
    }
    int query(int x)
    {
        if (q.size()==1) return q[0](x);
        if (intersect(q[0], q[1])>x) return q[0](x);
        int l=1, r=q.size();
        while (l+1<r)
        {
            int mid=(l+r)>>1;
            if (intersect(q[mid-1], q[mid])<=x) l=mid;
            else r=mid;
        }
		return q[l](x);
    }
    double intersect(line x, line y)
    {
        if (x.a==y.a) return -1e18;
        else return (double)(x.b-y.b)/(double)(y.a-x.a);
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
            cht->insert({a, b});
        }
        else
        {
            int x; cin>>x;
            cout<<cht->query(x)<<endl;
        }
    }
    return 0;
}