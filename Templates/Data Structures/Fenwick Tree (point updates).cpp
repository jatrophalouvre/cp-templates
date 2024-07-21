// https://codebreaker.xyz/problem/fenwicktree_easy
#include <iostream>
using namespace std;
using ll=long long;

const int N=100013;
int n, m;
ll s[N];

struct FWT
{
    ll v[N]={0};
    
    FWT() {}
    void upd(int pos, ll val)
    {
		pos++;
        while (pos<=n)
        {
            v[pos]+=val;
            pos+=(pos&-pos);
        }
    }
    ll qry(int pos)
    {
        ll ans=0;
        while (pos>0)
        {
            ans+=v[pos];
            pos-=(pos&-pos);
        }
        return ans;
    }
    ll qry(int l, int r)
    {
		l++; r++;
		return qry(r)-qry(l-1);
	}
} *fwt;

int main()
{
    fwt=new FWT();
    cin>>n>>m;
    for (int i=0; i<n; i++)
    {
        cin>>s[i];
        fwt->upd(i, s[i]);
    }
    
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int pos; ll val; cin>>pos>>val;
            fwt->upd(pos, val-s[pos]);
            s[pos]+=val-s[pos];
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<fwt->qry(l, r)<<endl;
        }
    }
    return 0;
}