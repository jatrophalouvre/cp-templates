// https://www.luogu.com.cn/problem/P3901
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll=long long;
using TIII=tuple<ll, ll, ll>;

const int N=100013, B=316;
int n, m;
int s[N];
vector<TIII> q;
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

int main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>s[i];
    for (int i=0; i<m; i++)
    {
        int l, r; cin>>l>>r;
        q.push_back({l, r, i});
    }
    sort(q.begin(), q.end(), [](TIII x, TIII y)
    {
        auto [xl, xr, xid]=x;
        auto [yl, yr, yid]=y;
        if (xl/B!=yl/B) return xl<yl;
        else if ((xl/B)&1) return xr<yr;
        else return xr>yr;
    });
    
    for (auto i:q)
    {
        auto [il, ir, id]=i;
        while (l>il) add(--l);
        while (r<ir) add(++r);
        while (l<il) del(l++);
        while (r>ir) del(r--);
        if (cur==ir-il+1) ans[id]="Yes";
        else ans[id]="No";
    }
    for (int i=0; i<m; i++) cout<<ans[i]<<endl;
    return 0;
}