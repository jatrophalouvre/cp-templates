// https://www.luogu.com.cn/problem/P1443
// livin' for the hope of it all

#include <iostream>
#include <cstring>
#include <queue>
#include <utility>
#define x first
#define y second
using namespace std;

using PII = pair<int, int>;
const int N=1013;
const int dx[]={-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[]={-1, 1, -2, 2, -2, 2, -1, 1};
int n, m;
int d[N][N];
PII st;

void bfs()
{
    bool vis[N][N]={0};
    queue<PII> q;
    
    q.push(st);
    d[st.x][st.y]=0;
    vis[st.x][st.y]=1;
    while (q.size())
    {
        PII u=q.front(); q.pop();
        for (int a=0; a<8; a++)
        {
            int tx=u.x+dx[a], ty=u.y+dy[a];
            if ((0>tx || tx>=n || 0>ty || ty>=m) || vis[tx][ty]) continue;
            d[tx][ty]=d[u.x][u.y]+1;
            vis[tx][ty]=1;
            q.push({tx, ty});
        }
    }
}

int main()
{
    memset(d, -1, sizeof(d));
    cin>>n>>m>>st.x>>st.y;
    
    bfs();
    for (int a=0; a<n; a++)
    {
        for (int b=0; b<m; b++) cout<<d[a][b]<<' ';
        cout<<endl;
    }
    return 0;
}