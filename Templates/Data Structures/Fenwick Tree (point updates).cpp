// https://codebreaker.xyz/problem/fenwicktree_easy
#include <iostream>
using namespace std;
using ll=long long;

const int N=100013;
int n, m;
ll a[N];

struct FWT
{
    ll v[N]={0};
    
    FWT()
    {
        for (int i=0; i<n; i++)
        {
            v[i]+=a[i];
            if ((i|i+1)<n) v[i|i+1]+=v[i];
        }
    }
    void upd(int p, ll z)
    {
        for (; p<n; p|=p+1) v[p]+=z;
    }
    ll qry(int p)
    {
        ll z=0;
        for (; p>=0; p=(p&p+1)-1) z+=v[p];
        return z;
    }
    ll qry(int l, int r)
    {
        return qry(r)-qry(l-1);
	}
} *fwt;

int main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>a[i];
    
    fwt=new FWT();
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int p; ll z; cin>>p>>z;
            fwt->upd(p, z-a[p]);
            a[p]=z;
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<fwt->qry(l, r)<<endl;
        }
    }
    return 0;
}