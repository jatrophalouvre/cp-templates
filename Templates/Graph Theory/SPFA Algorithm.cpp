// https://www.luogu.com.cn/problem/P4779
#include <iostream>
#include <queue>
#include <vector>
#define int long long
#define fir first
#define sec second
using namespace std;
using PII = pair<int, int>;

const int N=100013;
int n, m;
vector<PII> s[N];
int d[N];

void spfa()
{
    bool inq[N]={0};
    fill(d, d+n, 1e18);
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

signed main()
{
    cin>>n>>m;
    while (m--)
    {
        int x, y, z; cin>>x>>y>>z;
        s[x].push_back({y, z});
        s[y].push_back({x, z});
    }
    
    spfa();
    cout<<d[n-1]<<endl;
    return 0;
}