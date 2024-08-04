// https://www.luogu.com.cn/problem/B3647
#include <iostream>
using namespace std;
using ll=long long;

const int N=513;
int n, m;
ll d[N][N];

void floyd()
{
    for (int i=0; i<n; i++)
    {
        for (int u=0; u<n; u++)
        {
            for (int v=0; v<n; v++)
            {
                d[u][v]=min(d[u][v], d[u][i]+d[i][v]);
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++) d[i][j]=1e18;
        d[i][i]=0;
    }
    while (m--)
    {
        int u, v; ll w; cin>>u>>v>>w;
        d[u][v]=min(d[u][v], w);
        d[v][u]=min(d[v][u], w);
    }
    
    floyd();
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++) cout<<d[i][j]<<' ';
        cout<<endl;
    }
    return 0;
}