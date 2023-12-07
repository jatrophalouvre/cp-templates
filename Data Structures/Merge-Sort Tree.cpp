// -
// to be checked

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#define x first
#define y second
using namespace std;

using ll = long long;
using PII = pair<ll, ll>;
const int N=100013;
int n, m;
ll os[N];
PII s[N];

struct node
{
#define lb lptr->v.begin()
#define le lptr->v.end()
#define rb rptr->v.begin()
#define re rptr->v.end()
    
    int l, r, mid;
    vector<ll> v;
    node *lptr, *rptr;
    
    node(int L, int R)
    {
        l=L; r=R; mid=(l+r)>>1;
        if (l==r) v.push_back(s[l].y);
        else
        {
            lptr=new node(l, mid);
            rptr=new node(mid+1, r);
            merge(lb, le, rb, re, back_inserter(v));
        }
    }
    ll query(int x, int y, int k)
    {
        if (l==r) return v[0];
        int pos=upper_bound(lb, le, y)-lower_bound(lb, le, x);
        if (pos>=k) return lptr->query(x, y, k);
        else return rptr->query(x, y, k-pos);
    }
} *mstree;

int main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++)
    {
        cin>>os[a];
        s[a]={os[a], a};
    }
    sort(s, s+n);
    mstree=new node(0, n-1);
    
    while (m--)
    {
        int x, y, k; cin>>x>>y>>k;
        cout<<os[mstree->query(x, y, k)]<<endl;
    }
    return 0;
}