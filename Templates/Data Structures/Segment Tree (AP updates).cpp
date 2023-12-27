// https://www.luogu.com.cn/problem/P1438
// livin' for the hope of it all

#include <iostream>
#include <cassert>
using namespace std;

using ll = long long;
const int N=100013;
int n, m;
ll s[N];

struct node
{
    int l, r, mid;
    ll v, fir, diff;
    node *lptr, *rptr;
    
    node(int L, int R)
    {
        l=L; r=R; mid=(l+r)>>1;
        fir=diff=0;
        if (l==r)
        {
            lptr=rptr=nullptr;
            v=s[l];
        }
        else
        {
            lptr=new node(l, mid);
            rptr=new node(mid+1, r);
            v=lptr->v+rptr->v;
        }
    }
    void update(int x, int y, ll a, ll d)
    {
		if (l==x && r==y)
		{
			v+=a*(r-l+1)+d*(r-l+1)*(r-l)/2;
			fir+=a;
			diff+=d;
			return;
		}
		prop();
		if (y<=mid) lptr->update(x, y, a, d);
		else if (x>=mid+1) rptr->update(x, y, a, d);
		else
		{
			lptr->update(x, mid, a, d);
			rptr->update(mid+1, y, a+d*(mid-x+1), d);
		}
		v=lptr->v+rptr->v;
	}
	ll query(int pos)
	{
		if (l==r)
		{
			assert(l==pos);
			return v;
		}
		prop();
		if (pos<=mid) return lptr->query(pos);
		else return rptr->query(pos);
	}
	ll query(int x, int y)
	{
		if (l==x && r==y) return v;
		prop();
		if (y<=mid) return lptr->query(x, y);
		else if (x>=mid+1) return rptr->query(x, y);
		else return lptr->query(x, mid)+rptr->query(mid+1, y);
	}
	void prop()
	{
		if (fir==0 && diff==0) return;
		lptr->fir+=fir;
		rptr->fir+=fir+diff*(mid-l+1);
		lptr->diff+=diff;
		rptr->diff+=diff;
		lptr->v+=fir*(mid-l+1)+diff*(mid-l+1)*(mid-l)/2;
		rptr->v+=(fir+diff*(mid-l+1))*(r-mid)+diff*(r-mid)*(r-mid-1)/2;
		fir=diff=0;
	}
	void print()
	{
		if (l==r) return;
		prop();
		lptr->print();
		rptr->print();
	}
} *segtree;

int main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++) cin>>s[a];
    
    segtree=new node(0, n-1);
    while (m--)
    {
		int t; cin>>t;
		if (t==1)
		{
			int l, r; ll a, d; cin>>l>>r>>a>>d;
			segtree->update(l, r, a, d);
		}
		else
		{
			int pos; cin>>pos;
			cout<<segtree->query(pos)<<endl;
		}
	}
    return 0;
}