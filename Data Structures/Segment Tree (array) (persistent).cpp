// https://www.luogu.com.cn/problem/P3919
// to be reviewed

#include <iostream>
#include <cassert>
using namespace std;

using ll = long long;
const int N=100013;
int n, m;
int ver[N<<5];
ll s[N];

struct node
{
#define l L[u]
#define r R[u]
#define mid M[u]

    int L[N<<5], R[N<<5], M[N<<5];
    int lt[N<<5], rt[N<<5], i=0;
    ll v[N<<5];
    
    node(int LL, int RR) { build(ver[0], LL, RR); }
    void build(int &u, int LL, int RR)
    {
        u=++i;
        L[u]=LL; R[u]=RR; M[u]=(LL+RR)>>1;
        if (l==r)
        {
            v[u]=s[l];
            return;
        }
        build(lt[u], l, mid);
        build(rt[u], mid+1, r);
    }
    void update(int &u, int o, int pos, ll val)
    {
        u=++i;
        L[u]=L[o]; R[u]=R[o]; M[u]=M[o];
        lt[u]=lt[o]; rt[u]=rt[o];
        v[u]=v[o];
        if (l==r)
        {
            v[u]=val;
            return;
        }
        if (pos<=mid) update(lt[u], lt[o], pos, val);
        else update(rt[u], rt[o], pos, val);
    }
    ll query(int &u, int pos)
    {
        if (l==r) return v[u];
        if (pos<=mid) return query(lt[u], pos);
        else return query(rt[u], pos);
    }
    ll query(int &u, int x, int y)
    {
        if (x==l && r==y) return v[u];
        if (y<=mid) return query(lt[u], x, y);
        else if (x>mid) return query(rt[u], x, y);
        else return query(lt[u], x, mid)+query(rt[u], mid+1, y);
    }
} *psegtree;

int main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++) cin>>s[a];
    
    psegtree=new node(0, n-1);
    for (int a=1; a<=m; a++)
    {
        int o, t; cin>>o>>t;
        if (t==1)
        {
            int x; ll y; cin>>x>>y;
            psegtree->update(ver[a], ver[o], x, y);
        }
        else
        {
            int pos; cin>>pos;
            cout<<psegtree->query(ver[o], pos)<<endl;
            ver[a]=ver[o];
        }
    }
    return 0;
}