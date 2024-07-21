// -
#include <iostream>
using namespace std;
using ll=long long;

const int N=1013;
int n, m, q;
ll a[N][N];

struct FWT
{
	ll v[N][N]={0};
	
	FWT() {}
	void upd(int x, int y, ll val)
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
	ll qry(int x, int y)
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
	ll qry(int x1, int y1, int x2, int y2)
	{
		x2++; y2++;
		return qry(x2, y2)-qry(x2, y1)-qry(x1, y2)+qry(x1, y1);
	}
} *fwt;

int main()
{
	fwt=new FWT();
	cin>>n>>m;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<m; j++)
		{
			cin>>a[i][j];
			fwt->upd(i, j, a[i][j]);
		}
	}
	
	cin>>q;
	while (q--)
	{
		int t; cin>>t;
		if (t==1)
		{
			int x, y; ll val; cin>>x>>y>>val; 
			fwt->upd(x, y, val-a[x][y]);
			a[x][y]+=val-a[x][y];
		}
		else
		{
			int x1, y1, x2, y2; cin>>x1>>y1>>x2>>y2;
			cout<<fwt->qry(x1, y1, x2, y2)<<endl;
		}
	}
	return 0;
}