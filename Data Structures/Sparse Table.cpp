// https://www.luogu.com.cn/problem/P3865
// livin' for the hope of it all

#include <iostream>
using namespace std;

using ll = long long;
const int N=100013, L=22;
int n, m;
ll s[N];

struct node
{
    ll st[N][L], lg[N];
    
    node()
    {
        for (int a=2; a<=n; a++) lg[a]=lg[a>>1]+1;
        for (int a=0; a<n; a++) st[a][0]=s[a];

        for (int b=1; (1<<b)<=n; b++)
        {
            for (int a=0; a+(1<<b)-1<n; a++)
            {
                st[a][b]=max(st[a][b-1], st[a+(1<<(b-1))][b-1]);
            }
        }
    }
    ll query(int l, int r)
    {
        int i=lg[r-l+1];
        return max(st[l][i], st[r-(1<<i)+1][i]);
    }
} *st;

int main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++) cin>>s[a];
    st=new node();
    
    while (m--)
    {
        int x, y; cin>>x>>y;
        cout<<st->query(x, y)<<endl;
    }
    return 0;
}