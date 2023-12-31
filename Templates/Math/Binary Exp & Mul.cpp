// https://codebreaker.xyz/problem/exponentiate
// livin' for the hope of it all

#include <iostream>
#define int long long
using namespace std;

int n, m, mod;

int mul(int x, int y)
{
    int ans=0;
    x%=mod; y%=mod;
    while (y)
    {
        if (y&1) ans=(ans+x)%mod;
        x=(2*x)%mod;
        y>>=1;
    } 
    return ans;
}
int pow(int x, int y)
{
    int ans=1;
    x%=mod;
    while (y)
    {
        if (y&1) ans=(ans*x)%mod;
        x=(x*x)%mod;
        y>>=1;
    }
    return ans;
}

signed main()
{
    int t; cin>>t;
    while (t--)
    {
        cin>>n>>m>>mod;
        cout<<pow(n, m)<<endl;
    }
    return 0;
}