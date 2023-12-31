// https://www.luogu.com.cn/problem/P1379
// livin' for the hope of it all

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=4;
const int dx[]={-1, 0, 0, 1};
const int dy[]={0, -1, 1, 0};
int s[N][N];
string st, te="123804765";
unordered_map<string, int> d;

int de_bfs()
{
    if (st==te) return 0;
    unordered_map<string, int> vis;
    queue<string> q;
    
    q.push(st); q.push(te);
    vis[st]=1; vis[te]=2;
    d[st]=d[te]=0;
    while (q.size())
    {
        string u=q.front(); q.pop();
        string ne=u;
        int x, y, cnt=0;
        while (cnt<9)
        {
            s[cnt/3][cnt%3]=ne[cnt]-'0';
            if (ne[cnt]=='0') { x=cnt/3; y=cnt%3; }
            cnt++;
        }
        for (int a=0; a<4; a++)
        {
            int tx=x+dx[a], ty=y+dy[a];
            if (0>tx || tx>=3 || 0>ty || ty>=3) continue;
            swap(s[x][y], s[tx][ty]);
            ne="";
            for (int a=0; a<3; a++) for (int b=0; b<3; b++) ne+=(char)(s[a][b]+'0');
            
            if (vis[ne]==vis[u])
            {
                swap(s[x][y], s[tx][ty]);
                continue;
            }
            if ((vis[ne]==1 && vis[u]==2) || (vis[ne]==2 && vis[u]==1)) return d[ne]+d[u]+1;
            
            q.push(ne);
            d[ne]=d[u]+1;
            vis[ne]=vis[u];
            swap(s[x][y], s[tx][ty]);
        }
    }
    return -1;
}

signed main()
{
    cin>>st;
    cout<<de_bfs()<<endl;
}