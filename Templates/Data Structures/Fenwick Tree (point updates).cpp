// https://codebreaker.xyz/problem/fenwicktree_easy
// livin' for the hope of it all

#include <iostream>
#define int long long
using namespace std;

const int N=100013;
int n, m;
int s[N];

struct node
{
    int v[N]={0};
    
    node() {}
    void update(int pos, int val)
    {
		pos++;
        while (pos<=n)
        {
            v[pos]+=val;
            pos+=(pos&-pos);
        }
    }
    int query(int pos)
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
		return query(r)-query(l-1);
	}
} *fwtree;

signed main()
{
    fwtree=new node();
    cin>>n>>m;
    for (int a=0; a<n; a++)
    {
        cin>>s[a];
        fwtree->update(a, s[a]);
    }
    
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int pos, x; cin>>pos>>x;
            fwtree->update(pos, x-s[pos]);
            s[pos]+=x-s[pos];
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<fwtree->query(l, r)<<endl;
        }
    }
    return 0;
}
