// https://codebreaker.xyz/problem/exponentiate
// livin' for the hope of it all

#include <iostream>
using namespace std;

using ll = long long;
ll n, m, mod;

ll mul(ll x, ll y)
{
    ll ans=0;
    x%=mod; y%=mod;
    while (y)
    {
        if (y&1) ans=(ans+x)%mod;
        x=(2*x)%mod;
        y>>=1;
    } 
    return ans;
}
ll pow(ll x, ll y)
{
    ll ans=1;
    x%=mod;
    while (y)
    {
        if (y&1) ans=(ans*x)%mod;
        x=(x*x)%mod;
        y>>=1;
    }
    return ans;
}

int main()
{
    int t; cin>>t;
    while (t--)
    {
        cin>>n>>m>>mod;
        cout<<pow(n, m)<<endl;
    }
    return 0;
}