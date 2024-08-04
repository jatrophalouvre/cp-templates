// https://codebreaker.xyz/problem/pplow
#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;
using ll=long long;
using TIIII=tuple<ll, ll, ll, ll>;

const int N=243;
int n, m, q;
vector<TIIII> s;

struct SEG
{
    int l, r, mid;
    ll v, cnt, lz;
    SEG *lptr, *rptr;
    
    SEG(int L, int R)
    {
        l=L; r=R; mid=(l+r)>>1;
        v=lz=0; cnt=r-l+1;
        lptr=rptr=nullptr;
    }
    void build()
    {
        if (lptr==nullptr) lptr=new SEG(l, mid);
        if (rptr==nullptr) rptr=new SEG(mid+1, r);
    }
    void upd(int x, int y, int val)
    {
        if (l==x && r==y)
        {
            v+=val;
            lz+=val;
            return;
        }
        build();
        prop();
        if (y<=mid) lptr->upd(x, y, val);
        else if (x>mid) rptr->upd(x, y, val);
        else
        {
            lptr->upd(x, mid, val);
            rptr->upd(mid+1, y, val);
        }
        merge();
    }
    ll qry()
    {
        if (v==0) return 1e9-cnt;
        else return 1e9;
    }
    void prop()
    {
        if (lz==0) return;
        lptr->v+=lz;
        lptr->lz+=lz;
        rptr->v+=lz;
        rptr->lz+=lz;
        lz=0;
    }
    void merge()
    {
        if (lptr->v<rptr->v)
        {
            v=lptr->v;
            cnt=lptr->cnt;
        }
        else if (lptr->v>rptr->v)
        {
            v=rptr->v;
            cnt=rptr->cnt;
        }
        else
        {
            v=lptr->v;
            cnt=lptr->cnt+rptr->cnt;
        }
    }
} *seg;

int main()
{
    seg=new SEG(1, 1e9);
    cin>>n>>m>>q;
    while (q--)
    {
        int x1, y1, x2, y2; cin>>x1>>y1>>x2>>y2;
        s.push_back({x1, y1, y2, 1});
        s.push_back({x2+1, y1, y2, -1});
    }
    sort(s.begin(), s.end());
    
    ll cur=0, ans=0;
    for (int i=0; i<s.size(); i++)
    {
        auto [t, l, r, val]=s[i];
        if (i>0) ans+=cur*(t-get<0>(s[i-1]));
        seg->upd(l, r, val);
        cur=seg->qry();
    }
    cout<<ans<<endl;
    return 0;
}