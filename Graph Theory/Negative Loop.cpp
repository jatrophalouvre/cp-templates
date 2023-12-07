// https://www.luogu.com.cn/problem/P3385
// livin' for the hope of it all

#include <iostream>
#include <cstdint>
#include <cstring>
#include <queue>
#include <utility>
#define x first
#define y second
using namespace std;

using ll = long long;
using PII = pair<ll, ll>;
const int N=100013, M=5000013;
int n, m;
int h[N], e[M], ne[M], idx=0;
ll w[M], d[N];

void spfa()
{
    bool inq[N]={0}; int cnt[N]={0};
    for (int a=0; a<n; a++) d[a]=INT64_MAX;
    queue<int> q;
    
    q.push(0);
    d[0]=0;
    inq[0]=1;
    cnt[0]=0;
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
                cnt[v]=cnt[u]+1;
                if (cnt[v]>n)
                {
                    cout<<"YES"<<endl;
                    return;
                }
                if (!inq[v])
                {
                    q.push(v);
                    inq[v]=1;
                }
            }
        }
    }
    cout<<"NO"<<endl;
    return;
}

int main()
{
    
    memset(h, -1, sizeof(h));
    cin>>n>>m;
    while (m--)
    {
        int x, y; ll z; cin>>x>>y>>z;
        e[idx]=y; w[idx]=z; ne[idx]=h[x]; h[x]=idx++;
        if (z>=0) { e[idx]=x; w[idx]=z; ne[idx]=h[y]; h[y]=idx++; } //problem-specific step
    }
    
    spfa();
    return 0;
}