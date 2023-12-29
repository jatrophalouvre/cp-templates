// https://codeforces.com/problemset/problem/438/D
// to be reviewed

#include <iostream>
#include <cassert>
using namespace std;

using ll = long long;
const int N=100013;
int n, m;
ll s[N];

struct node
{
    int l, r, mid;
    ll sum, v;
    node *lptr, *rptr;
    
    node(int L, int R)
    {
        l=L; r=R; mid=(l+r)>>1;
        if (l==r)
        {
            lptr=rptr=nullptr;
            sum=v=s[l];
        }
        else
        {
            lptr=new node(l, mid);
            rptr=new node(mid+1, r);
            sum=lptr->sum+rptr->sum;
            v=max(lptr->v, rptr->v);
        }
    }
    void update(int pos, ll val)
    {
        if (l==r)
        {
            assert(l==pos);
            sum=v=val;
            return;
        }
        if (pos<=mid) lptr->update(pos, val);
        else rptr->update(pos, val);
        sum=lptr->sum+rptr->sum;
        v=max(lptr->v, rptr->v);
    }
    void update(int x, int y, ll val)
    {
        if (v<val) return;
        if (l==r)
        {
            assert(x<=l && l<=y);
            v%=val; sum%=val;
            return;
        }
        if (y<=mid) lptr->update(x, y, val);
        else if (x>=mid+1) rptr->update(x, y, val);
        else
        {
            lptr->update(x, mid, val);
            rptr->update(mid+1, y, val);
        }
        sum=lptr->sum+rptr->sum;
        v=max(lptr->v, rptr->v);
    }
    ll query(int pos)
    {
        if (l==r)
        {
            assert(l==pos);
            return v;
        }
        if (pos<=mid) return lptr->query(pos);
        else return rptr->query(pos);
    }
    ll query(int x, int y)
    {
        if (l==x && r==y) return sum;
        if (y<=mid) return lptr->query(x, y);
        else if (x>=mid+1) return rptr->query(x, y);
        else return lptr->query(x, mid)+rptr->query(mid+1, y);
    }
} *segtree;

int main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++) cin>>s[a];
    
    segtree=new node(0, n-1);
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int pos; ll val; cin>>pos>>val;
            segtree->update(pos, val);
        }
        else if (t==2)
        {
            int l, r; ll val; cin>>l>>r>>val;
            segtree->update(l, r, val);
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<segtree->query(l, r)<<endl;
        }
    }
    return 0;
}
