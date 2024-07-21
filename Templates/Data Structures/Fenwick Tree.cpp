// https://www.luogu.com.cn/problem/P3372
#include <iostream>
using namespace std;
using ll=long long;

const int N=100013;
int n, m;
ll s[N];

struct FWT
{
    ll v1[N]={0}, v2[N]={0};
    
    FWT() {}
    void upd(ll v[N], int pos, ll val)
    {
        while (pos<=n)
        {
            v[pos]+=val;
            pos+=(pos&-pos);
        }
    }
    void upd(int l, int r, ll val)
    {
        l++; r++;
        upd(v1, l, val); upd(v1, r+1, -val);
        upd(v2, l, l*val); upd(v2, r+1, -(r+1)*val);
    }
    ll qry(ll v[N], int pos)
    {
        ll ans=0;
        while (pos>0)
        {
            ans+=v[pos];
            pos-=(pos&-pos);
        }
        return ans;
    }
    ll qry(int l, int r)
    {
		l++; r++;
        return (ll(r+1)*qry(v1, r)-qry(v2, r))-(ll(l)*qry(v1, l-1)-qry(v2, l-1));
    }
} *fwt;

int main()
{
    fwt=new FWT();
    cin>>n>>m;
    for (int i=0; i<n; i++)
    {
        cin>>s[i];
        fwt->upd(i, i, s[i]);
    }
    
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int l, r; ll val; cin>>l>>r>>val;
            fwt->upd(l, r, val);
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<fwt->qry(l, r)<<endl;
        }
    }
    return 0;
}