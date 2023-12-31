// https://codebreaker.xyz/problem/candyboxes
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
void merge(int x, int y)
{
    x=find(x); y=find(y);
    if (x==y) return;
    g[y]=x;
}
void del(int x, int y)
{
    int tx=find(x); y=find(y);
    if (tx==y) return;
    g[x]=y;
}

signed main()
{
    cin>>n>>m;
    for (int a=1, b=n+1; a<=n && b<=2*n; a++, b++) g[a]=g[b]=b;
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int x, y; cin>>x>>y;
            merge(x, y);
        }
        else if (t==2)
        {
            int x, y; cin>>x>>y;
            del(x, y);
        }
        else
        {
            int x, y; cin>>x>>y;
            if (find(x)==find(y)) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }
    return 0;
}