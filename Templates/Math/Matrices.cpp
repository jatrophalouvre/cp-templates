// -
// to be checked

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=13;
int n;
int mod;

struct node
{
    int n, m;
    int s[N][N]={0};
    
    node(int N, int M) { n=N; m=M; }
    void read()
    {
        cin>>n>>m;
        for (int a=0; a<n; a++) for (int b=0; b<m; b++) cin>>s[a][b];
    }
    void print()
    {
        for (int a=0; a<n; a++)
        {
            for (int b=0; b<m; b++) cout<<s[a][b]<<' ';
            cout<<endl;
        }
    }
};
node MUL(node x, node y)
{
    node ans(x.n, y.m);
    for (int a=0; a<x.n; a++)
    {
        for (int b=0; b<y.m; b++)
        {
            for (int c=0; c<x.m; c++)
            {
                ans.s[a][b]=(ans.s[a][b]+(x.s[a][c]*y.s[c][b])%mod)%mod;
            }
        }
    }
    return ans;
}
node POW(node x, int y)
{
    node ans(x.n, x.m);
    for (int a=0; a<x.n; a++) ans.s[a][a]=1;

    while (y)
    {
        if (y&1) ans=MUL(ans, x);
        x=MUL(x, x);
        y>>=1;
    }
    return ans;
}

signed main()
{
    cin>>n>>mod;
    node b(2, 2);
    b.s[0][0]=b.s[0][1]=b.s[1][0]=1;

    cout<<(POW(b, n+1).s[0][0]-1)%mod<<endl;
    return 0;
}