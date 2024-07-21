// https://www.luogu.com.cn/problem/P3372
#include <iostream>
using namespace std;
using ll=long long;

const int N=100013, B=316;
int n, m;
int s[N];

struct SD
{
    int lptr[N], rptr[N];
    ll v[N]={0}, lz[N]={0};
    
    SD()
    {
        for (int j=0; j*B<n; j++)
        {
            lptr[j]=j*B;
            rptr[j]=min((j+1)*B-1, n-1);
            for (int i=lptr[j]; i<=rptr[j]; i++) v[j]+=s[i];
        }
    }
    void upd(int pos, ll val)
    {
        v[pos/B]+=val-s[pos];
        s[pos]+=val-s[pos];
    }
    void upd(int l, int r, ll val)
    {
        int bl=l/B, br=r/B;
        if (bl==br)
        {
            for (int i=l; i<=r; i++) s[i]+=val;
            v[bl]+=val*(r-l+1);
        }
        else
        {
            for (int j=bl+1; j<=br-1; j++)
            {
                v[j]+=val*(rptr[j]-lptr[j]+1);
                lz[j]+=val;
            }
            for (int i=l; i<=rptr[bl]; i++) s[i]+=val;
            v[bl]+=val*(rptr[bl]-l+1);
            for (int i=lptr[br]; i<=r; i++) s[i]+=val;
            v[br]+=val*(r-lptr[br]+1);
        }
    }
    ll qry(int pos) { return s[pos]+lz[pos/B]; }
    ll qry(int l, int r)
    {
        ll ans=0;
        int bl=l/B, br=r/B;
        if (bl==br) for (int i=l; i<=r; i++) ans+=s[i]+lz[bl];
        else
        {
            for (int j=bl+1; j<=br-1; j++) ans+=v[j];
            for (int i=l; i<=rptr[bl]; i++) ans+=s[i]+lz[bl];
            for (int i=lptr[br]; i<=r; i++) ans+=s[i]+lz[br];
        }
        return ans;
    }
} *sd;

int main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>s[i];
    
    sd=new SD();
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int l, r; ll val; cin>>l>>r>>val;
            sd->upd(l, r, val);
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<sd->qry(l, r)<<endl;
        }
    }
    return 0;
}