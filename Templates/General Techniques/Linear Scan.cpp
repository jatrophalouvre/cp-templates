// https://codebreaker.xyz/problem/hdb
// livin' for the hope of it all

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=100013;
int n, m;
int s[N];
vector<int> st[3];
int dp[3][N];

void scan(int a)
{
    sort(st[a&1].begin(), st[a&1].end());
    for (auto b:st[a&1]) dp[a&1][b]=INT64_MAX;
    int c, minn;
    
    // scan left
    c=0, minn=INT64_MAX;
    for (auto b:st[a&1])
    {
        while (c<st[1-a&1].size() && st[1-a&1][c]<=b)
        {
            minn=min(minn, dp[1-a&1][st[1-a&1][c]]-(st[1-a&1][c]-*st[1-a&1].begin())*s[a]);
            c++;
        }
        if (minn!=INT64_MAX) dp[a&1][b]=min(dp[a&1][b], minn+(b-st[1-a&1][0])*s[a]);
    }
    
    // scan right
    c=st[1-a&1].size()-1, minn=INT64_MAX;
    for (int _=st[a&1].size()-1; _>=0; _--)
    {
        int b=st[a&1][_];
        while (c>=0 && st[1-a&1][c]>=b)
        {
            minn=min(minn, dp[1-a&1][st[1-a&1][c]]-(*st[1-a&1].rbegin()-st[1-a&1][c])*s[a]);
            c--;
        }
        if (minn!=INT64_MAX) dp[a&1][b]=min(dp[a&1][b], minn-(b-*st[1-a&1].rbegin())*s[a]);
    }
}

signed main()
{
    cin>>n>>m;
    for (int a=1; a<=n; a++)
    {
        int t; cin>>s[a]>>t;
        st[a&1].clear();
        while (t--)
        {
            int x; cin>>x;
            st[a&1].push_back(x);
        }
        
        if (a==1)
        {
            for (int b=1; b<=m; b++) dp[a&1][b]=(b-1)*s[1];
            continue;
        }
        else scan(a);
    }
    int ans=INT64_MAX;
    for (auto b:st[1-n&1]) ans=min(ans, dp[1-n&1][b]+abs(b-m)*s[n]);
    cout<<ans<<endl;
    return 0;
}