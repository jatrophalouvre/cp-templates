// https://codebreaker.xyz/problem/hdb
#include <iostream>
#include <algorithm>
#include <vector>
#define int long long
using namespace std;

const int N=100013;
int n, m;
int s[N];
vector<int> st[3];
int dp[3][N];

void scan(int i)
{
    sort(st[i&1].begin(), st[i&1].end());
    for (auto b:st[i&1]) dp[i&1][b]=1e18;
    int k, minn;
    
    // scan left
    k=0, minn=1e18;
    for (auto j:st[i&1])
    {
        while (k<st[1-i&1].size() && st[1-i&1][k]<=j)
        {
            minn=min(minn, dp[1-i&1][st[1-i&1][k]]-(st[1-i&1][k]-*st[1-i&1].begin())*s[i]);
            k++;
        }
        if (minn!=1e18) dp[i&1][j]=min(dp[i&1][j], minn+(j-st[1-i&1][0])*s[i]);
    }
    
    // scan right
    k=st[1-i&1].size()-1, minn=1e18;
    for (int _=st[i&1].size()-1; _>=0; _--)
    {
        int j=st[i&1][_];
        while (k>=0 && st[1-i&1][k]>=j)
        {
            minn=min(minn, dp[1-i&1][st[1-i&1][k]]-(*st[1-i&1].rbegin()-st[1-i&1][k])*s[i]);
            k--;
        }
        if (minn!=1e18) dp[i&1][j]=min(dp[i&1][j], minn-(j-*st[1-i&1].rbegin())*s[i]);
    }
}

signed main()
{
    cin>>n>>m;
    for (int i=1; i<=n; i++)
    {
        int t; cin>>s[i]>>t;
        st[i&1].clear();
        while (t--)
        {
            int x; cin>>x;
            st[i&1].push_back(x);
        }
        
        if (i==1)
        {
            for (int j=1; j<=m; j++) dp[i&1][j]=(j-1)*s[1];
            continue;
        }
        else scan(i);
    }
    int ans=1e18;
    for (auto j:st[1-n&1]) ans=min(ans, dp[1-n&1][j]+abs(j-m)*s[n]);
    cout<<ans<<endl;
    return 0;
}