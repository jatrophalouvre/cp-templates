// https://codebreaker.xyz/problem/hdb
// livin' for the hope of it all

#include <iostream>
#include <algorithm>
#include <cstdint>
#include <vector>
#define curst st[a&1]
#define prevst st[1-a&1]
#define curdp dp[a&1]
#define prevdp dp[1-a&1]
using namespace std;

using ll = long long;
const int N=100013;
int n, m;
ll s[N];
vector<int> st[3];
ll dp[3][N];

void scan(int a)
{
    sort(curst.begin(), curst.end());
    for (auto b:st[a&1]) curdp[b]=INT64_MAX;
    int c; ll minn;
    
    c=0, minn=INT64_MAX;
    for (auto b:curst)
    {
        while (c<prevst.size() && prevst[c]<=b)
        {
            minn=min(minn, prevdp[prevst[c]]-(prevst[c]-*prevst.begin())*s[a]);
            c++;
        }
        if (minn!=INT64_MAX) curdp[b]=min(curdp[b], minn+(b-prevst[0])*s[a]);
    }
    
    c=prevst.size()-1, minn=INT64_MAX;
    for (int _=curst.size()-1; _>=0; _--)
    {
        int b=curst[_];
        while (c>=0 && prevst[c]>=b)
        {
            minn=min(minn, prevdp[prevst[c]]-(*prevst.rbegin()-prevst[c])*s[a]);
            c--;
        }
        if (minn!=INT64_MAX) curdp[b]=min(curdp[b], minn-(b-*prevst.rbegin())*s[a]);
    }
}

int main()
{
    cin>>n>>m;
    for (int a=1; a<=n; a++)
    {
        int t; cin>>s[a]>>t;
        curst.clear();
        while (t--)
        {
            int x; cin>>x;
            curst.push_back(x);
        }
        
        if (a==1)
        {
            for (int b=1; b<=m; b++) curdp[b]=(b-1)*s[1];
            continue;
        }
        else scan(a);
    }
    ll ans=INT64_MAX;
    for (auto b:st[1-n&1]) ans=min(ans, dp[1-n&1][b]+abs(b-m)*s[n]);
    cout<<ans<<endl;
    return 0;
}