// https://www.luogu.com.cn/problem/P4779
// livin' for the hope of it all

#include <iostream>
#include <cstdint>
#include <queue>
#include <utility>
#include <vector>
#define fir first
#define sec second
using namespace std;

using ll = long long;
using PII = pair<ll, ll>;
const int N=100013, M=5000013;
int n, m;
vector<PII> s[N];
ll d[N];

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
        
        for (auto [v, w]:s[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
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
    cin>>n>>m;
    while (m--)
    {
        int x, y; ll z; cin>>x>>y>>z;
        s[x].push_back({y, z});
        s[y].push_back({x, z});
    }
    
    spfa();
    for (int a=0; a<n; a++) cout<<d[a]<<' '; cout<<endl;
    return 0;
}
