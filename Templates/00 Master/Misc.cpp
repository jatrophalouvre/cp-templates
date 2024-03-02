// __int128
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

// Custom Hash
struct CHASH
{
    int h[N];
    
    CHASH() { fill(h, h+N, -1); }
    int add(int x)
    {
        int p=x%N;
        while (h[p]!=-1)
        {
            if (h[p]==x) return p;
            p=(p+1)%N;
        }
    }
    int find(int x)
    {
        int p=x%N;
        while (h[p]!=-1)
        {
            if (h[p]==x) return p;
            p=(p+1)%N;
        }
    }
} *chash;

// Discretization
void discretize()
{
    vector<int> t; for (int i=0; i<n; i++) t.push_back(s[i]);
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    for (int i=0; i<n; i++) s[i]=lower_bound(t.begin(), t.end(), s[i])-t.begin();
}

// Optimizations
#define getchar() getchar_unlocked()
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;

inline int read()
{
	int x=0, f=1; char c=getchar();
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
inline void print(int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x>9) print(x/10);
	putchar(x%10+'0');
}

// PBDS
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define pbds_map gp_hash_table<int, int>;
#define pbds_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;
#define pbds_multiset tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>; // cannot erase()

// Stress Testing
#include <chrono>
#include <random>

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct WRONG
{
    signed main() {}
} *wrong;

struct CORRECT
{
    signed main() {}
} *correct;

signed main()
{
    for (int _=0; _<100013; _++)
    {
        wrong=new WRONG; correct=new CORRECT;
        int out_wrong=wrong->main();
        int out_correct=correct->main();
        if (out_wrong!=out_correct)
        {
            cerr<<endl;
            cerr<<"WRONG: "<<out_wrong<<endl;
            cerr<<"CORRECT: "<<out_correct<<endl;
            return 0;
        }
        cerr<<"PASSED "<<_<<endl;
    }
    cerr<<"PASSED ALL"<<endl;
    return 0;
}