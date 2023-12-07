// https://codebreaker.xyz/problem/midas
// livin' for the hope of it all

#include <iostream>
#include <cstdint>
#include <queue>
using namespace std;

using ll = long long;
const int N=100013;
int n, m;
int l[N], r[N];
ll d[N];

void pbfs()
{
    for (int a=0; a<n; a++) d[a]=INT64_MAX;
    deque<int> q;
    
    q.push_back(0);
    d[0]=0;
    while (q.size())
    {
        int u=q.front(); q.pop_front();
        if (l[u]!=-1)
        {
            if (d[l[u]]>d[u]*2)
            {
                d[l[u]]=d[u]*2;
                q.push_front(l[u]);
            }
        }
        if (r[u]!=-1)
        {
            if (d[r[u]]>d[u]*2+1)
            {
                d[r[u]]=d[u]*2+1;
                q.push_back(r[u]);
            }
        }
    }
}

int main()
{
    cin>>n;
    for (int a=0; a<n; a++) cin>>l[a]>>r[a];
    
    pbfs();
    cin>>m;
    while (m--)
    {
        int x, y; cin>>x>>y;
        if (d[x]>=d[y]) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}