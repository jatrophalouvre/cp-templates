// https://www.luogu.com.cn/problem/P3372
#include <iostream>
#define int long long
using namespace std;

const int N=100013, B=316;
int n, m;
int s[N];

struct SD
{
    int lptr[N], rptr[N];
    int v[N]={0}, lazy[N]={0};
    
    SD()
    {
        for (int j=0; j*B<n; j++)
        {
            lptr[j]=j*B;
            rptr[j]=min((j+1)*B-1, n-1);
            for (int i=lptr[j]; i<=rptr[j]; i++) v[j]+=s[i];
        }
    }
    void update(int pos, int val)
    {
        v[pos/B]+=val-s[pos];
        s[pos]+=val-s[pos];
    }
    void update(int l, int r, int val)
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
                lazy[j]+=val;
            }
            for (int i=l; i<=rptr[bl]; i++) s[i]+=val;
            v[bl]+=val*(rptr[bl]-l+1);
            for (int i=lptr[br]; i<=r; i++) s[i]+=val;
            v[br]+=val*(r-lptr[br]+1);
        }
    }
    int query(int pos) { return s[pos]+lazy[pos/B]; }
    int query(int l, int r)
    {
        int ans=0;
        int bl=l/B, br=r/B;
        if (bl==br) for (int i=l; i<=r; i++) ans+=s[i]+lazy[bl];
        else
        {
            for (int j=bl+1; j<=br-1; j++) ans+=v[j];
            for (int i=l; i<=rptr[bl]; i++) ans+=s[i]+lazy[bl];
            for (int i=lptr[br]; i<=r; i++) ans+=s[i]+lazy[br];
        }
        return ans;
    }
} *sd;

signed main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>s[i];
    
    sd=new SD();
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int l, r, val; cin>>l>>r>>val;
            sd->update(l, r, val);
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<sd->query(l, r)<<endl;
        }
    }
    return 0;
}