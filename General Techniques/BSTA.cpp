// https://codebreaker.xyz/problem/justright
// livin' for the hope of it all

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;
ll n, m;
vector<ll> s;

ll bsta(ll x)
{
    ll ans=0; int r;
    for (int l=1; l<=n; l++)
    {
        auto it=upper_bound(s.begin(), s.end(), x+s[l-1]);
        if (it==s.begin()) continue;
        it--;
        r=it-s.begin();
        if (l<=r && s[r]-s[l-1]<=x) ans+=r-l+1;
    }
    return ans;
}

int main()
{
    cin>>n>>m; s.resize(n+1); s[0]=0;
    m=n*(n+1)/2-m+1;
    for (int a=1; a<=n; a++)
    {
        cin>>s[a];
        s[a]+=s[a-1];
    }
    
    ll l=0, r=1e18;
    while (l+1<r)
    {
        ll mid=(l+r)>>1, ans=bsta(mid);
        if (ans<m) l=mid;
        else r=mid;
    }
    cout<<r<<endl;
    return 0;
}