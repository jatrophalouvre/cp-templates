// https://www.luogu.com.cn/problem/P3865
#include <iostream>
#define int long long
using namespace std;

const int N=100013, L=22;
int n, m;
int s[N];

struct ST
{
    int st[N][L], lg[N]={0};
    
    ST()
    {
        for (int i=2; i<=n; i++) lg[i]=lg[i>>1]+1;
        for (int i=0; i<n; i++) st[i][0]=s[i];
        
        for (int j=1; (1<<j)<=n; j++)
        {
            for (int i=0; i+(1<<j)-1<n; i++)
            {
                st[i][j]=max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int query(int l, int r)
    {
        int i=lg[r-l+1];
        return max(st[l][i], st[r-(1<<i)+1][i]);
    }
} *st;

signed main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>s[i];
    
    st=new ST();
    while (m--)
    {
        int x, y; cin>>x>>y;
        cout<<st->query(x, y)<<endl;
    }
    return 0;
}