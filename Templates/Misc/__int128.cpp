// -
// livin' for the hope of it all

#include <bits/stdc++.h>
#define int long long
//#define getchar() getchar_unlocked()
using namespace std;

using bll = __int128;

inline bll read()
{
	bll x=0, f=1; char c=getchar();
	while (c<'0' || c>'9')
	{
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0' && c<='9')
	{
		x=x*10+(c-'0');
		c=getchar();
	}
	return x*f;
}
inline void print(bll x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x>9) print(x/10);
	putchar(x%10+'0');
}

signed main()
{
    int t; cin>>t;
    while (t--)
    {
        print(read());
        cout<<endl;
    }
    return 0;
}