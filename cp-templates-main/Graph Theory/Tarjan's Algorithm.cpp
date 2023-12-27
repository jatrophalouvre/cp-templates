//livin' for the hope of it all

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

using ll = long long;
const int N=100013, M=5000013;
int n, m;
int h[N], e[M], ne[M], idx=0;
ll pre[N], post[N], i=0;
bool cut[N];

void tarjan(int u, int r)
{
    pre[u]=post[u]=i++;
    int cnt=0;
    
    for (int a=h[u]; ~a; a=ne[a])
    {
        int v=e[a];
        if (pre[v]==-1)
        {
            tarjan(v, r);
            post[u]=min(post[u], post[v]);
            if (post[v]>=pre[u] && u!=r) cut[u]=true;
            if (u==r) cnt++;
        }
        else post[u]=min(post[u], pre[v]);
    }
    if (cnt>=2 && u==r) cut[u]=true;
}

int main()
{
    memset(h, -1, sizeof(h));
    memset(pre, -1, sizeof(pre));
    cin>>n>>m;
    while (m--)
    {
        int x, y; cin>>x>>y;
        e[idx]=y; ne[idx]=h[x]; h[x]=idx++;
        e[idx]=x; ne[idx]=h[y]; h[y]=idx++;
    }
    for (int a=0; a<n; a++) if (pre[a]==-1) tarjan(a, a);
    
    int ans=0;
    for (int a=0; a<n; a++) if (cut[a]) ans++; cout<<ans<<endl;
    for (int a=0; a<n; a++) if (cut[a]) cout<<a<<' '; cout<<endl;
    return 0;
}