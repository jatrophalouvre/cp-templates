// https://www.luogu.com.cn/problem/P6824
#include <iostream>
using namespace std;

const int N=100013, L=22;
int n, m;

struct TR
{
    int ne[N][3], idx=1;
    int sz[N];
    
    TR()
    {
        for (int i=0; i<N; i++)
        {
            for (int j=0; j<3; j++)
            {
                ne[i][j]=-1;
            }
        }
    }
    void ins(int x)
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
    int qry(int x)
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
} *tr;

int main()
{
    tr=new TR();
    cin>>n>>m;
    for (int i=0; i<n; i++)
    {
        int x; cin>>x;
        tr->ins(x);
    }
    
    int ans=0;
    for (int i=0; i<(1<<L); i++)
    {
        ans=max(ans, tr->qry(i));
        if (ans==n) break;
    }
    cout<<ans<<endl;
    return 0;
}