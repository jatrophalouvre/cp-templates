// https://www.luogu.com.cn/problem/P3834
// livin' for the hope of it all

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=100013;
int n, m;
int s[N], ind[N];

struct node
{
    int l, r, mid;
    vector<int> v;
    node *lptr, *rptr;
    
    node(int L, int R)
    {
        l=L; r=R; mid=(l+r)>>1;
        if (l==r)
        {
            lptr=rptr=nullptr;
            v.push_back(ind[l]);
        }
        else
        {
            lptr=new node(l, mid);
            rptr=new node(mid+1, r);
            merge(lptr->v.begin(), lptr->v.end(), rptr->v.begin(), rptr->v.end(), back_inserter(v));
        }
    }
    int query(int x, int y, int k)
    {
        if (l==r) return v[0];
        int pos=upper_bound(lptr->v.begin(), lptr->v.end(), y)-lower_bound(lptr->v.begin(), lptr->v.end(), x);
        if (pos>=k) return lptr->query(x, y, k);
        else return rptr->query(x, y, k-pos);
    }
} *mstree;

signed main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++)
    {
        cin>>s[a];
        ind[a]=a;
    }
    
    sort(ind, ind+n, [](int x, int y) { return s[x]<s[y]; });
    mstree=new node(0, n-1);
    while (m--)
    {
        int x, y, k; cin>>x>>y>>k;
        cout<<s[mstree->query(x, y, k)]<<endl;
    }
    return 0;
}