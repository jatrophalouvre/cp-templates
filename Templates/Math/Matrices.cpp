// -
// to be checked

#include <iostream>
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
        for (int i=0; i<n; i++) for (int j=0; j<m; j++) cin>>s[i][j];
    }
    void print()
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<m; j++) cout<<s[i][j]<<' ';
            cout<<endl;
        }
    }
};
node MUL(node x, node y)
{
    node ans(x.n, y.m);
    for (int i=0; i<x.n; i++)
    {
        for (int j=0; j<y.m; j++)
        {
            for (int k=0; k<x.m; k++)
            {
                ans.s[i][j]=(ans.s[i][j]+(x.s[i][k]*y.s[k][j])%mod)%mod;
            }
        }
    }
    return ans;
}
node POW(node x, int y)
{
    node ans(x.n, x.m);
    for (int i=0; i<x.n; i++) ans.s[i][i]=1;

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