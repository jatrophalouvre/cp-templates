// https://codeforces.com/problemset/problem/1791/F
#include <iostream>
using namespace std;
using ll=long long;

const int N=100013;
int n, m;
ll s[N];

struct SEG
{
    int l, r, mid;
    ll sum, v;
    SEG *lptr, *rptr;
    
    SEG(int L, int R)
    {
        l=L; r=R; mid=(l+r)>>1;
        if (l==r)
        {
            lptr=rptr=nullptr;
            sum=v=s[l];
        }
        else
        {
            lptr=new SEG(l, mid);
            rptr=new SEG(mid+1, r);
            sum=lptr->sum+rptr->sum;
            v=max(lptr->v, rptr->v);
        }
    }
    void upd(int x, int y)
    {
        if (v<10) return;
        if (l==r)
        {
            sum=v=sod(v);
            return;
        }
        if (y<=mid) lptr->upd(x, y);
        else if (x>mid) rptr->upd(x, y);
        else
        {
            lptr->upd(x, mid);
            rptr->upd(mid+1, y);
        }
        sum=lptr->sum+rptr->sum;
        v=max(lptr->v, rptr->v);
    }
    ll qry(int pos)
    {
        if (l==r) return v;
        if (pos<=mid) return lptr->qry(pos);
        else return rptr->qry(pos);
    }
    ll qry(int x, int y)
    {
        if (l==x && r==y) return sum;
        if (y<=mid) return lptr->qry(x, y);
        else if (x>mid) return rptr->qry(x, y);
        else return lptr->qry(x, mid)+rptr->qry(mid+1, y);
    }
    ll sod(ll x)
    {
        string str=to_string(x);
        ll ans=0;
        for (auto i:str) ans+=int(i-'0');
        return ans;
    }
} *seg;

int main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>s[i];
    
    seg=new SEG(0, n-1);
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int l, r; cin>>l>>r; l--; r--;
            seg->upd(l, r);
        }
        else
        {
            int pos; cin>>pos; pos--;
            cout<<seg->qry(pos)<<endl;
        }
    }
}