// -
// to be checked

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#define x first
#define y second
using namespace std;

using ll = long long;
using PII = pair<ll, ll>;
const int N=100013;
int n, m;
ll os[N];
PII s[N];

struct node
{
#define lt u*2
#define rt u*2+1
#define l L[u]
#define r R[u]
#define mid M[u]
    
    int L[N<<2], R[N<<2], M[N<<2];
    vector<ll> v[N<<2];
    
    node(int LL, int RR) { build(1, LL, RR); }
    void build(int u, int LL, int RR)
    {
        L[u]=LL; R[u]=RR; M[u]=(LL+RR)>>1;
        if (l==r)
        {
            v[u].push_back(s[l].y);
            return;
        }
        build(lt, l, mid);
        build(rt, mid+1, r);
        merge(v[lt].begin(), v[lt].end(), v[rt].begin(), v[rt].end(), back_inserter(v[u]));
    }
    ll query(int u, int x, int y, int k)
    {
        if (l==r) return v[u][0];
        int pos=upper_bound(v[lt].begin(), v[lt].end(), y)-lower_bound(v[lt].begin(), v[lt].end(), x);
        if (pos>=k) return query(lt, x, y, k);
        else return query(rt, x, y, k-pos);
    }
} *mstree;

int main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++)
    {
        cin>>os[a];
        s[a]={os[a], a};
    }
    sort(s, s+n);
    mstree=new node(0, n-1);
    
    while (m--)
    {
        int x, y, k; cin>>x>>y>>k;
        cout<<os[mstree->query(1, x, y, k)]<<endl;
    }
    return 0;
}