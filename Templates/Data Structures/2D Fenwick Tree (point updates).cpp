// to be checked
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
	void upd(int x, int y, ll z)
	{
		for (; x<n; x|=x+1)
		{
			for (int ty=y; ty<n; ty|=ty+1)
			{
				v[x][ty]+=z;
			}
		}
	}
	ll qry(int x, int y)
	{
		ll ans=0;
		for (; x>=0; x=(x&x+1)-1)
		{
			for (int ty=y; ty>=0; ty=(ty&ty+1)-1)
			{
				ans+=v[x][ty];
			}
		}
		return ans;
	}
	ll qry(int x1, int y1, int x2, int y2)
	{
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
			int x, y; ll z; cin>>x>>y>>z; 
			fwt->upd(x, y, z-a[x][y]);
			a[x][y]=z;
		}
		else
		{
			int x1, y1, x2, y2; cin>>x1>>y1>>x2>>y2;
			cout<<fwt->qry(x1, y1, x2, y2)<<endl;
		}
	}
	return 0;
}