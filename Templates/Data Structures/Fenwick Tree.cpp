// https://www.luogu.com.cn/problem/P3372
// livin' for the hope of it all

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=100013;
int n, m;
int s[N];

struct node
{
    int v1[N]={0}, v2[N]={0};
    
    node() {}
    void add(int v[N], int pos, int x)
    {
        while (pos<=n)
        {
            v[pos]+=x;
            pos+=(pos&-pos);
        }
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
    void update(int l, int r, int x)
    {
		l++; r++;
        add(v1, l, x);
        add(v1, r+1, -x);
        add(v2, l, l*x);
        add(v2, r+1, -(r+1)*x);
    }
    int query(int l, int r)
    {
		l++; r++;
        return ((r+1)*query(v1, r)-query(v2, r))-((l*query(v1, l-1))-query(v2, l-1));
    }
} *fwtree;

signed main()
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
            int l, r, val; cin>>l>>r>>val;
            fwtree->update(l, r, val);
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<fwtree->query(l, r)<<endl;
        }
    }
    return 0;
}