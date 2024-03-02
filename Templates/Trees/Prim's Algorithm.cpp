// https://www.luogu.com.cn/problem/P3366
#include <iostream>
#include <queue>
#include <vector>
#define int long long
#define fir first
#define sec second
using namespace std;
using PII=pair<int, int>;

const int N=100013;
int n, m;
vector<PII> s[N];

int prim()
{
    int key[N]; bool vis[N]={0};
    fill(key, key+n, 1e18);
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    q.push({0, 0});
    key[0]=0;
    while (q.size())
    {
        int u=q.top().sec; q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        for (auto [v, w]:s[u])
        {
            if (key[v]>w)
            {
                key[v]=w;
                q.push({key[v], v});
            }
        }
    }
    
    int ans=0;
    for (int u=1; u<n; u++) ans+=key[u];
    return ans;
}

int main()
{
    cin>>n>>m;
    while (m--)
    {
        int u, v, w; cin>>u>>v>>w;
        s[u].push_back({v, w});
        s[v].push_back({u, w});
    }
    
    cout<<prim()<<endl;
    return 0;
}