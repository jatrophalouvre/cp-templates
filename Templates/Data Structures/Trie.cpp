// https://www.luogu.com.cn/problem/P6824
#include <iostream>
using namespace std;
using ll=long long;

const int N=100013, L=22;
int n, m;

struct TRIE
{
    int ne[N][3], idx=1;
    int sz[N];
    
    TRIE() { for (int i=0; i<3; i++) fill(ne[i], ne[i]+N, -1); }
    void insert(int x)
    {
        int u=0;
        for (int i=L; i>=0; i--)
        {
            int cur=(x>>i)&1;
            if (ne[u][cur]==-1) ne[u][cur]=idx++;
            u=ne[u][cur];
            sz[u]++;
        }
    }
    int query(int x)
    {
        int u=0, ans=0;
        bool flag=1;
        for (int i=L; i>=0; i--)
        {
            int cur=(x>>i)&1, req=(m>>i)&1;
            cur^=req;
            if (req==1 && ne[u][!cur]!=-1) ans+=sz[ne[u][!cur]];
            if (ne[u][cur]==-1)
            {
                flag=0;
                break;
            }
            u=ne[u][cur];
        }
        if (flag) ans+=sz[u];
        return ans;
    }
} *trie;

int main()
{
    trie=new TRIE();
    cin>>n>>m;
    for (int i=0; i<n; i++)
    {
        int x; cin>>x;
        trie->insert(x);
    }
    
    int ans=0;
    for (int i=0; i<(1<<L); i++)
    {
        ans=max(ans, trie->query(i));
        if (ans==n) break;
    }
    cout<<ans<<endl;
    return 0;
}