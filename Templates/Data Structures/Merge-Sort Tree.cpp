// to be checked
// SPOJ KQUERY
// https://www.luogu.com.cn/problem/SP3266
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll=long long;

const int N=30013;
int n, m;
ll a[N], ans=0;

struct MST
{
    int l, r, mid;
    vector<ll> v;
    MST *lptr, *rptr;
    
    MST(int L, int R)
    {
        l=L; r=R; mid=(l+r)/2;
        if (l==r) v={a[l]};
        else
        {
            lptr=new MST(l, mid);
            rptr=new MST(mid+1, r);
            merge(lptr->v.begin(), lptr->v.end(), rptr->v.begin(), rptr->v.end(), back_inserter(v));
        }
    }
    int qry(int x, int y, int k)
    {
        if (l==x && r==y) return v.end()-upper_bound(v.begin(), v.end(), k);
        if (y<=mid) return lptr->qry(x, y, k);
        else if (x>mid) return rptr->qry(x, y, k);
        else return lptr->qry(x, mid, k)+rptr->qry(mid+1, y, k);
    }
} *mst;

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for (int i=0; i<n; i++) cin>>a[i];
    
    mst=new MST(0, n-1);
    cin>>m;
    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a^=ans;
        b^=ans;
        c^=ans;
        if(a<1) a = 1;
        if(b>n) b = n;
        if(a>b){
            ans = 0;
        }
        else{
            ans = mst->qry(a-1,b-1,c);
        }
        printf("%d\n",ans);
    }
    return 0;
}