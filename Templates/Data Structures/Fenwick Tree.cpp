// https://www.luogu.com.cn/problem/P3372
#include <iostream>
#define int long long
using namespace std;

const int N=100013;
int n, m;
int s[N];

struct FWT
{
    int v1[N], v2[N];
    
    FWT() {}
    void update(int v[N], int pos, int val)
    {
        while (pos<=n)
        {
            v[pos]+=val;
            pos+=(pos&-pos);
        }
    }
    void update(int l, int r, int val)
    {
        l++; r++;
        update(v1, l, val); update(v1, r+1, -val);
        update(v2, l, l*val); update(v2, r+1, -(r+1)*val);
    }
    int query(int v[N], int pos)
    {
        int ans=0;
        while (pos>0)
        {
            ans+=v[pos];
            pos-=(pos&-pos);
        }
        return ans;
    }
    int query(int l, int r)
    {
		l++; r++;
        return ((r+1)*query(v1, r)-query(v2, r))-(l*query(v1, l-1)-query(v2, l-1));
    }
} *fwt;

signed main()
{
    fwt=new FWT();
    cin>>n>>m;
    for (int i=0; i<n; i++)
    {
        cin>>s[i];
        fwt->update(i, i, s[i]);
    }
    
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int l, r, val; cin>>l>>r>>val;
            fwt->update(l, r, val);
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<fwt->query(l, r)<<endl;
        }
    }
    return 0;
}