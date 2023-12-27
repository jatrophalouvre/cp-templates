// https://codebreaker.xyz/problem/problematicjourney
// livin' for the hope of it all

#include <iostream>
#include <cstdint>
#include <cstring>
#include <queue>
using namespace std;

using ll = long long;
const int N=100013, M=5000013;
int n, m;
int h[N], e[M], ne[M], idx=0;
ll d[N];

void bfs()
{
    bool vis[N]={0};
    queue<int> q;
    
    q.push(0);
    d[0]=0;
    vis[0]=1;
    while (q.size())
    {
        int u=q.front(); q.pop();
        for (int a=h[u]; ~a; a=ne[a])
        {
            int v=e[a];
            if (vis[v]) continue;
            d[v]=d[u]+1;
            vis[v]=1;
            q.push(v);
        }
    }
}

int main()
{
    memset(h, -1, sizeof(h));
    cin>>n>>m;
    while (m--)
    {
        int x, y; cin>>x>>y;
        e[idx]=y; ne[idx]=h[x]; h[x]=idx++;
        e[idx]=x; ne[idx]=h[y]; h[y]=idx++;
    }
    
    bfs();
    cout<<d[n-1]<<endl;
    return 0;
}