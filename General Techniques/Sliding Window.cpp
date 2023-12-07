// https://codebreaker.xyz/problem/catfight
// livin' for the hope of it all

#include <iostream>
using namespace std;

using ll = long long;
const int N=100013;
int n, m, ans=0;
ll s[N];

int main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++) cin>>s[a];
    
    int r=-1; ll sum=0;
    for (int l=0; l<n; l++)
    {
        if (l>0) sum-=s[l-1];
        while (r+1<n && sum+s[r+1]<m) { r++; sum+=s[r]; }
        ans=max(ans, r-l+1);
    }
    cout<<ans<<endl;
    return 0;
}