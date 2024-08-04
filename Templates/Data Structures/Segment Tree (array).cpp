// https://codebreaker.xyz/problem/fenwicktree_easy
#include <iostream>
using namespace std;
using ll=long long;

const int N=100013;
int n, m;
ll a[N]={0};

struct SEG
{
    ll v[N*2];
    
    SEG()
    {
        for (int i=0; i<n; i++) v[i+n]=a[i];
        for (int i=n-1; i>0; i--) v[i]=v[i*2]+v[i*2+1];
    }
    void upd(int p, ll z)
    {
        for (v[p+=n]=z; p>1; p/=2) v[p/2]=v[p]+v[p^1];
    }
    ll qry(int l, int r)
    {
        ll ans=0;
        for (l+=n, r+=n+1; l<r; l/=2, r/=2)
        {
            if (l&1) ans+=v[l++];
            if (r&1) ans+=v[--r];
        }
        return ans;
    }
} *seg;

int main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>a[i];
    
    seg=new SEG();
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int p; ll z; cin>>p>>z;
            seg->upd(p, z);
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<seg->qry(l, r)<<endl;
        }
    }
    return 0;
}