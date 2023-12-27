// https://www.luogu.com.cn/problem/P1908
// livin' for the hope of it all

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;
const int N=100013;
int n;
ll s[N];

ll dnc(int l, int r)
{
    if (l==r) return 0;
    int mid=(l+r)>>1;
    vector<int> t;
    for (int a=l; a<=mid; a++) t.push_back(s[a]);
    sort(t.begin(), t.end());
    
    ll ans=dnc(l, mid)+dnc(mid+1, r);
    for (int a=mid+1; a<=r; a++) ans+=t.size()-(upper_bound(t.begin(), t.end(), s[a])-t.begin());
    return ans;
}

int main()
{
    cin>>n;
    for (int a=0; a<n; a++) cin>>s[a];
    cout<<dnc(0, n-1)<<endl;
    return 0;
}