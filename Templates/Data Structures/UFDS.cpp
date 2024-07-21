// https://www.luogu.com.cn/problem/P3367
#include <iostream>
using namespace std;
using ll=long long;

const int N=100013;
int n, m;
int dsu[N];

int find(int x)
{
    if (dsu[x]==x) return x;
    else return dsu[x]=find(dsu[x]);
}
bool unite(int x, int y)
{
    x=find(x); y=find(y);
    if (x==y) return 0;
    dsu[y]=x;
    return 1;
}

int main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) dsu[i]=i;
    
    while (m--)
    {
        int t, x, y; cin>>t>>x>>y;
        if (t==1) unite(x, y);
        else if (find(x)==find(y)) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}