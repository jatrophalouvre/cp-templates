// https://www.luogu.com.cn/problem/P3372
// livin' for the hope of it all

#include <iostream>
using namespace std;

using ll = long long;
const int N=100013;
int n, m;
ll s[N];

struct node
{
    ll v1[N]={0}, v2[N]={0};
    
    node() {}
    void add(ll v[N], int pos, ll x)
    {
        while (pos<=n)
        {
            v[pos]+=x;
            pos+=(pos&-pos);
        }
    }
    ll query(ll v[N], int pos)
    {
        ll ans=0;
        while (pos>0)
        {
            ans+=v[pos];
            pos-=(pos&-pos);
        }
        return ans;
    }
    void update(int l, int r, ll x)
    {
		l++; r++;
        add(v1, l, x);
        add(v1, r+1, -x);
        add(v2, l, l*x);
        add(v2, r+1, -(r+1)*x);
    }
    ll query(int l, int r)
    {
		l++; r++;
        return ((r+1)*query(v1, r)-query(v2, r))-((l*query(v1, l-1))-query(v2, l-1));
    }
} *fwtree;

int main()
{
    fwtree=new node();
    cin>>n>>m;
    for (int a=0; a<n; a++)
    {
        cin>>s[a];
        fwtree->update(a, a, s[a]);
    }
    
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int l, r; ll x; cin>>l>>r>>x;
            fwtree->update(l, r, x);
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<fwtree->query(l, r)<<endl;
        }
    }
    return 0;
}