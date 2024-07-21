// https://www.luogu.com.cn/problem/B3694
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll=long long;

const int N=100013;
int n;
ll s[N];

void discretize()
{
    vector<ll> t; for (int i=0; i<n; i++) t.push_back(s[i]);
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    for (int i=0; i<n; i++) s[i]=lower_bound(t.begin(), t.end(), s[i])-t.begin();
}

int main()
{
    cin>>n;
    for (int i=0; i<n; i++) cin>>s[i];
    discretize();
    for (int i=0; i<n; i++) cout<<s[i]<<' ';
    cout<<endl;
    return 0;
}