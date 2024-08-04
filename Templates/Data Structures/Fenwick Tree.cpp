// https://www.luogu.com.cn/problem/P3372
#include <iostream>
using namespace std;
using ll=long long;

const int N=100013;
int n, m;
ll a[N];

struct FWT
{
    ll v1[N]={0}, v2[N]={0};
    
    FWT()
    {
        for (int i=0; i<n; i++)
        {
            v1[i]+=a[i]-(i>0?a[i-1]:0);
            if ((i|i+1)<n) v1[i|i+1]+=v1[i];
            
			v2[i]+=i*a[i]-(i>0?i*a[i-1]:0);
			if ((i|i+1)<n) v2[i|i+1]+=v2[i];
        }
    }
    void upd(ll v[N], int p, ll z)
    {
        for (; p<n; p|=p+1) v[p]+=z;
    }
    void upd(int l, int r, ll z)
    {
        upd(v1, l, z); upd(v1, r+1, -z);
        upd(v2, l, z*l); upd(v2, r+1, -z*(r+1));
    }
    ll qry(ll v[N], int p)
    {
        ll ans=0;
        for (; p>=0; p=(p&p+1)-1) ans+=v[p];
        return ans;
    }
    ll qry(int l, int r)
    {
        return (qry(v1, r)*(r+1)-qry(v2, r))-(qry(v1, l-1)*l-qry(v2, l-1));
    }
} *fwt;

int main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>a[i];
	
    fwt=new FWT();
    while (m--)
    {
        int t, l, r; cin>>t>>l>>r;
        if (t==1)
        {
            ll z; cin>>z;
            fwt->upd(l, r, z);
        }
        else cout<<fwt->qry(l, r)<<endl;
    }
    return 0;
}