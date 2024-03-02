// https://codebreaker.xyz/problem/segmenttreebeats
#include <iostream>
#define int long long
using namespace std;

const int N=100013;
int n, m;
int s[N];

struct SEG
{
    int l, r, mid;
    int sum, v;
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
    void update(int x, int y)
    {
        if (v<10) return;
        if (l==r)
        {
            sum=v=sod(v);
            return;
        }
        if (y<=mid) lptr->update(x, y);
        else if (x>=mid+1) rptr->update(x, y);
        else
        {
            lptr->update(x, mid);
            rptr->update(mid+1, y);
        }
        sum=lptr->sum+rptr->sum;
        v=max(lptr->v, rptr->v);
    }
    int query(int pos)
    {
        if (l==r) return v;
        if (pos<=mid) return lptr->query(pos);
        else return rptr->query(pos);
    }
    int query(int x, int y)
    {
        if (l==x && r==y) return sum;
        if (y<=mid) return lptr->query(x, y);
        else if (x>=mid+1) return rptr->query(x, y);
        else return lptr->query(x, mid)+rptr->query(mid+1, y);
    }
    int sod(int x)
    {
        string str=to_string(x);
        int ans=0;
        for (auto i:str) ans+=(int)(i-'0');
        return ans;
    }
} *seg;

signed main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>s[i];
    
    seg=new SEG(0, n-1);
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int l, r; cin>>l>>r;
            seg->update(l, r);
        }
        else
        {
            int pos; cin>>pos;
            cout<<seg->query(pos)<<endl;
        }
    }
    return 0;
}