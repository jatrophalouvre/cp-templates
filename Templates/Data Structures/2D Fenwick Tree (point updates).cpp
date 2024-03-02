// -
#include <iostream>
#define int long long
using namespace std;

const int N=1013;
int n, m, q;
int s[N][N];

struct FWT
{
	int v[N][N];
	
	FWT() {}
	void update(int x, int y, int val)
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
	int query(int x, int y)
	{
		int ans=0;
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
	int query(int x1, int y1, int x2, int y2)
	{
		x2++; y2++;
		return query(x2, y2)-query(x2, y1)-query(x1, y2)+query(x1, y1);
	}
} *fwt;

signed main()
{
	fwt=new FWT();
	cin>>n>>m;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<m; j++)
		{
			cin>>s[i][j];
			fwt->update(i, j, s[i][j]);
		}
	}
	
	cin>>q;
	while (q--)
	{
		int t; cin>>t;
		if (t==1)
		{
			int x, y, val; cin>>x>>y>>val;
			fwt->update(x, y, val-s[x][y]);
			s[x][y]+=val-s[x][y];
		}
		else
		{
			int x1, y1, x2, y2; cin>>x1>>y1>>x2>>y2;
			cout<<fwt->query(x1, y1, x2, y2)<<endl;
		}
	}
	return 0;
}