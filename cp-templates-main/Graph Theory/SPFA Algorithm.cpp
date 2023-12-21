// https://www.luogu.com.cn/problem/P4779
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
ll w[M], d[N];

void spfa()
{
    bool inq[N]={0};
    for (int a=0; a<n; a++) d[a]=INT64_MAX;
    queue<int> q;
    
    q.push(0);
    d[0]=0;
    inq[0]=1;
    while (q.size())
    {
        int u=q.front(); q.pop();
        inq[u]=0;
        
        for (int a=h[u]; ~a; a=ne[a])
        {
            int v=e[a];
            if (d[v]>d[u]+w[a])
            {
                d[v]=d[u]+w[a];
                if (!inq[v])
                {
                    q.push(v);
                    inq[v]=1;
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
        int x, y; ll z; cin>>x>>y>>z;
        e[idx]=y; w[idx]=z; ne[idx]=h[x]; h[x]=idx++;
        e[idx]=x; w[idx]=z; ne[idx]=h[y]; h[y]=idx++;
    }
    
    spfa();
    for (int a=0; a<n; a++) cout<<d[a]<<' '; cout<<endl;
    return 0;
}