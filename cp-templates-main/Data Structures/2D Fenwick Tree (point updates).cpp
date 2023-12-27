// -
// livin' for the hope of it all

#include <iostream>
using namespace std;

using ll = long long;
const int N=1000;
int n, m, q;
ll s[N][N];

struct node
{
	ll v[N][N];
	
	node() {}
	void update(int x, int y, ll val)
	{
		x++; y++;
		while (x<=n)
		{
			int ty=y;
			while (ty<=n)
			{
				v[x][ty]+=val;
				ty+=(ty&-ty);
			}
			x+=(x&-x);
		}
	}
	ll query(int x, int y)
	{
		ll ans=0;
		while (x>0)
		{
			int ty=y;
			while (ty>0)
			{
				ans+=v[x][ty];
				ty-=(ty&-ty);
			}
			x-=(x&-x);
		}
		return ans;
	}
	ll query(int x1, int y1, int x2, int y2)
	{
		x2++; y2++;
		return query(x2, y2)-query(x2, y1)-query(x1, y2)+query(x1, y1);
	}
	int get(int x, int y) { return x*m+y; }
} *fwtree;

int main()
{
	fwtree=new node();
	cin>>n>>m;
	for (int a=0; a<n; a++)
	{
		for (int b=0; b<m; b++)
		{
			cin>>s[a][b];
			fwtree->update(a, b, s[a][b]);
		}
	}
	
	cin>>q;
	while (q--)
	{
		int t; cin>>t;
		if (t==1)
		{
			int x, y; ll val; cin>>x>>y>>val;
			fwtree->update(x, y, val);
		}
		else
		{
			int x1, y1, x2, y2; cin>>x1>>y1>>x2>>y2;
			cout<<fwtree->query(x1, y1, x2, y2)<<endl;
		}
	}
	return 0;
}
