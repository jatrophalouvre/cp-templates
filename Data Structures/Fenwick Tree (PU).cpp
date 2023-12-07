// https://codebreaker.xyz/problem/fenwicktree_easy
// livin' for the hope of it all

#include <iostream>
#include <cstring>
using namespace std;

using ll = long long;
const int N=100013;
int n, m;
ll s[N];

struct node
{
    ll v[N]={0};
    
    node() {}
    int lowbit(int x) { return x&-x; }
    void update(int pos, ll x)
    {
        while (pos<=n)
        {
            v[pos]+=x;
            pos+=lowbit(pos);
        }
    }
    ll query(int pos)
    {
        ll ans=0;
        while (pos>0)
        {
            ans+=v[pos];
            pos-=lowbit(pos);
        }
        return ans;
    }
    ll query(int l, int r) { return query(r)-query(l-1); }
} *fwtree;

int main()
{
    fwtree=new node();
    cin>>n>>m;
    for (int a=1; a<=n; a++)
    {
        cin>>s[a];
        fwtree->update(a, s[a]);
    }
    
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int pos; ll x; cin>>pos>>x; pos++;
            fwtree->update(pos, x-s[pos]);
            s[pos]+=x-s[pos];
        }
        else
        {
            int l, r; cin>>l>>r; l++; r++;
            cout<<fwtree->query(l, r)<<endl;
        }
    }
    return 0;
}