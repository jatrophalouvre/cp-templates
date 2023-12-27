// https://www.luogu.com.cn/problem/P4667
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
int w[N];
ll d[N];

void bfs()
{
    for (int a=0; a<n; a++) d[a]=INT64_MAX;
    deque<int> q;
    
    q.push_back(0);
    d[0]=0;
    while (q.size())
    {
        int u=q.front(); q.pop_front();
        for (int a=h[u]; ~a; a=ne[a])
        {
            int v=e[a];
            if (w[a]==0)
            {
                if (d[v]>d[u])
                {
                    d[v]=d[u];
                    q.push_front(v);
                }
            }
            else
            {
                if (d[v]>d[u]+1)
                {
                    d[v]=d[u]+1;
                    q.push_back(v);
                }
            }
        }
    }
}

int main()
{
    memset(h, -1, sizeof(h));
    cin>>n>>m;
    while (m--)
    {
        int x, y, z; cin>>x>>y>>z;
        e[idx]=y; w[idx]=z; ne[idx]=h[x]; h[x]=idx++;
        e[idx]=x; w[idx]=z; ne[idx]=h[y]; h[y]=idx++;
    }
    
    bfs();
    cout<<d[n-2]<<endl;
    return 0;
}