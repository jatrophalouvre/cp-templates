// https://codebreaker.xyz/problem/bobek
// livin' for the hope of it all

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;
const int N=43, M=1<<20;
int n, m, n1, n2;
ll s[N];
vector<ll> l, r;

void init()
{
    n1=n/2, n2=n-n1;
    
    for (int a=0; a<(1<<n1); a++)
    {
        ll sum=0;
        for (int b=0; b<n1; b++) if ((a>>b)&1) sum+=s[b];
        l.push_back(sum);
    }
    
    for (int a=0; a<(1<<n2); a++)
    {
        ll sum=0;
        for (int b=0; b<n2; b++) if ((a>>b)&1) sum+=s[n1+b];
        r.push_back(sum);
    }
    
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
}

int main()
{
    cin>>n>>m;
    for (ll a=0; a<n; a++) cin>>s[a];
    
    init();
    int rptr=(1<<n2); ll ans=0;
    for (int lptr=0; lptr<(1<<n1); lptr++)
    {
        while (rptr-1>=0 && l[lptr]+r[rptr-1]>m) rptr--;
        ans+=rptr;
    }
    cout<<ans<<endl;
    return 0;
}