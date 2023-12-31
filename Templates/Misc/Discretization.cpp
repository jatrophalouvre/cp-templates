// https://www.luogu.com.cn/problem/B3694
// livin' for the hope of it all

#include <bits/stdc++.h>
#define int long long
using namespace std;

int n;
vector<int> s;

void discretize()
{
    vector<int> t=s;
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    for (int a=0; a<n; a++) s[a]=lower_bound(t.begin(), t.end(), s[a])-t.begin();
}

signed main()
{
    cin>>n; s.resize(n);
    for (int a=0; a<n; a++) cin>>s[a];
    discretize();
    for (int a=0; a<n; a++) cout<<s[a]<<' ';
    cout<<endl;
    return 0;
}
