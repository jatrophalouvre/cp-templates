// https://www.luogu.com.cn/problem/B3647
// livin' for the hope of it all

#include <iostream>
using namespace std;

using ll = long long;
const int N=513;
int n, m;
ll d[N][N];

void floyd()
{
    for (int a=0; a<n; a++)
    {
        for (int u=0; u<n; u++)
        {
            for (int v=0; v<n; v++)
            {
                d[u][v]=min(d[u][v], d[u][a]+d[a][v]);
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++)
    {
        for (int b=0; b<n; b++) d[a][b]=1e18;
        d[a][a]=0;
    }
    while (m--)
    {
        int x, y; ll z; cin>>x>>y>>z;
        d[x][y]=d[y][x]=z;
    }
    
    floyd();
    for (int a=0; a<n; a++)
    {
        for (int b=0; b<n; b++)
        {
            cout<<d[a][b]<<' ';
        }
        cout<<endl;
    }
    return 0;
}