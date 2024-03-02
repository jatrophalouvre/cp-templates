// https://www.luogu.com.cn/problem/P4667
#include <iostream>
#include <queue>
#define int long long
#define fir first
#define sec second
using namespace std;
using PII=pair<int, int>;

const int N=100013;
int n, m;
vector<PII> s[N];
int d[N];

void bfs()
{
    fill(d, d+n, 1e18);
    deque<int> q;
    
    q.push_back(0);
    d[0]=0;
    while (q.size())
    {
        int u=q.front(); q.pop_front();
        for (auto [v, w]:s[u])
        {
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                if (w==0) q.push_front(v);
                else q.push_back(v);
            }
        }
    }
}

signed main()
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
