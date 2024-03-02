// https://codebreaker.xyz/problem/fenwicktree_easy
#include <iostream>
#define int long long
using namespace std;

const int N=100013;
int n, m;
int s[N];

struct FWT
{
    int v[N]={0};
    
    FWT() {}
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
} *fwt;

signed main()
{
    fwt=new FWT();
    cin>>n>>m;
    for (int i=0; i<n; i++)
    {
        cin>>s[i];
        fwt->update(i, s[i]);
    }
    
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int pos, val; cin>>pos>>val;
            fwt->update(pos, val-s[pos]);
            s[pos]+=val-s[pos];
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<fwt->query(l, r)<<endl;
        }
    }
    return 0;
}