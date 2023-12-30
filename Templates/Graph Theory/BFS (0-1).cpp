// https://www.luogu.com.cn/problem/P4667
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

void bfs()
{
    for (int a=0; a<n; a++) d[a]=INT64_MAX;
    deque<int> q;
    
    q.push_back(0);
    d[0]=0;
    while (q.size())
    {
        int u=q.front(); q.pop_front();
        for (auto [v, w]:s[u])
        {
            if (w==0)
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
    cin>>n>>m;
    while (m--)
    {
        int x, y, z; cin>>x>>y>>z;
        s[x].push_back({y, z});
        s[y].push_back({x, z});
    }
    
    bfs();
    cout<<d[n-1]<<endl;
    return 0;
}
