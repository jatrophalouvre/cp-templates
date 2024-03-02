// https://www.luogu.com.cn/problem/P3901
#include <iostream>
#include <algorithm>
#include <vector>
#define int long long
using namespace std;

const int N=100013, B=316;
int n, m;
int s[N];
struct node { int l, r, i; }; vector<node> q;
int cnt[N]={0}; string ans[N];
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

signed main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>s[i];
    for (int i=0; i<m; i++)
    {
        int l, r; cin>>l>>r;
        q.push_back({l, r, i});
    }
    sort(q.begin(), q.end(), [](node x, node y)
    {
        if (x.l/B!=y.l/B) return x.l<y.l;
        else if ((x.l/B)&1) return x.r<y.r;
        else return x.r>y.r;
    });
    
    for (auto i:q)
    {
        while (l<i.l) del(l++);
        while (l>i.l) add(--l);
        while (r<i.r) add(++r);
        while (r>i.r) del(r--);
        if (cur==i.r-i.l+1) ans[i.i]="Yes";
        else ans[i.i]="No";
    }
    for (int i=0; i<m; i++) cout<<ans[i]<<endl;
    return 0;
}