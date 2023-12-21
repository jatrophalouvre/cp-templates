// https://www.luogu.com.cn/problem/P3901
// livin' for the hope of it all

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

const int N=100013;
int n, m, B;
int s[N];
struct node { int x, y, id; }; vector<node> q;
int cnt[N]={0}, ans[N];
int l=0, r=-1, cur=0;

void add(int pos)
{
    cnt[s[pos]]++;
    if (cnt[s[pos]]==1) cur++;
}
void del(int pos)
{
    cnt[s[pos]]--;
    if (cnt[s[pos]]==0) cur--;
}

int main()
{
    cin>>n>>m; B=sqrt(m); q.resize(m);
    for (int a=0; a<n; a++) cin>>s[a];
    for (int a=0; a<m; a++)
    {
        cin>>q[a].x>>q[a].y;
        q[a].id=a;
    }
    sort(q.begin(), q.end(), [](node x, node y)
    {
        if (x.x/B!=y.x/B) return x.x<y.x;
        else if ((x.x/B)&1) return x.y<y.y;
        else return x.y>y.y;
    });
    
    for (int a=0; a<m; a++)
    {
        while (l<q[a].x) del(l++);
        while (l>q[a].x) add(--l);
        while (r<q[a].y) add(++r);
        while (r>q[a].y) del(r--);
        if (cur==q[a].y-q[a].x+1) ans[q[a].id]=1;
        else ans[q[a].id]=0;
    }
    for (int a=0; a<m; a++)
    {
        if (ans[a]==1) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}