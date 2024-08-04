// -
#include <iostream>
//#define getchar() getchar_unlocked()
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
using ll=long long;

inline ll read()
{
	ll x=0, f=1; char c=getchar();
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
inline void print(ll x)
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
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t=read();
    while (t--)
    {
        print(read());
		putchar('\n');
    }
    return 0;
}