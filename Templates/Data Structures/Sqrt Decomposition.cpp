// https://www.luogu.com.cn/problem/P3372
#include <iostream>
using namespace std;
using ll=long long;

const int N=100013, B=316;
int n, m;
ll a[N];

struct SD
{
    int st[N], te[N];
    ll v[N]={0}, lz[N]={0};
    
    SD()
    {
        for (int j=0; j*B<n; j++)
        {
            st[j]=j*B;
            te[j]=min((j+1)*B-1, n-1);
            for (int i=st[j]; i<=te[j]; i++) v[j]+=a[i];
        }
    }
    void upd(int p, ll z)
    {
        v[p/B]+=z-a[p];
        a[p]=z;
    }
    void upd(int l, int r, ll z)
    {
        int bl=l/B, br=r/B;
        if (bl==br)
        {
            for (int i=l; i<=r; i++) a[i]+=z;
            v[bl]+=z*(r-l+1);
        }
        else
        {
            for (int j=bl+1; j<=br-1; j++)
            {
                v[j]+=z*(te[j]-st[j]+1);
                lz[j]+=z;
            }
            for (int i=l; i<=te[bl]; i++) a[i]+=z;
            v[bl]+=z*(te[bl]-l+1);
            for (int i=st[br]; i<=r; i++) a[i]+=z;
            v[br]+=z*(r-st[br]+1);
        }
    }
    ll qry(int p) { return a[p]+lz[p/B]; }
    ll qry(int l, int r)
    {
        ll ans=0;
        int bl=l/B, br=r/B;
        if (bl==br) for (int i=l; i<=r; i++) ans+=a[i]+lz[bl];
        else
        {
            for (int j=bl+1; j<=br-1; j++) ans+=v[j];
            for (int i=l; i<=te[bl]; i++) ans+=a[i]+lz[bl];
            for (int i=st[br]; i<=r; i++) ans+=a[i]+lz[br];
        }
        return ans;
    }
} *sd;

int main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>a[i];
    
    sd=new SD();
    while (m--)
    {
        int t, l, r; cin>>t>>l>>r; l--; r--;
        if (t==1)
        {
            ll z; cin>>z;
            sd->upd(l, r, z);
        }
        else cout<<sd->qry(l, r)<<endl;
    }
    return 0;
}