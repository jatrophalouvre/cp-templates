// https://www.luogu.com.cn/problem/B3694
// livin' for the hope of it all

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;
int n;
vector<ll> s;

void discretize()
{
    vector<ll> t=s;
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    for (int a=0; a<n; a++) s[a]=lower_bound(t.begin(), t.end(), s[a])-t.begin();
}

int main()
{
    cin>>n; s.resize(n);
    for (int a=0; a<n; a++) cin>>s[a];
    discretize();
    for (int a=0; a<n; a++) cout<<s[a]<<' ';
    cout<<endl;
    return 0;
}
