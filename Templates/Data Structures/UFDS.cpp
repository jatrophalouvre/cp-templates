// https://www.luogu.com.cn/problem/P3367
// livin' for the hope of it all

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=100013;
int n, m;
int g[N];

int find(int x)
{
    if (x==g[x]) return x;
    else return g[x]=find(g[x]);
}
void unite(int x, int y)
{
    x=find(x); y=find(y);
    if (x==y) return;
    g[y]=x;
}

signed main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++) g[a]=a;
    while (m--)
    {
        int t, x, y; cin>>t>>x>>y;
        if (t==1) unite(x, y);
        else if (find(x)==find(y)) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}