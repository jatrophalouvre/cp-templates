// -
#include <iostream>
//#define getchar() getchar_unlocked()
using namespace std;
using ll=long long;
using bll=__int128;

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

int main()
{
    int t; cin>>t;
    while (t--)
    {
        print(read());
        cout<<endl;
    }
    return 0;
}