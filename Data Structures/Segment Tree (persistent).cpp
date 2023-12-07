// https://www.luogu.com.cn/problem/P3919
// to be completed

#include <iostream>
#include <cassert>
using namespace std;

using ll = long long;
const int N=100013;
int n, m;
ll s[N];

struct node
{
#define lv lptr->v
#define rv rptr->v
    
    int l, r, mid;
    ll v;
    node *lptr, *rptr;
    
    node(int L, int R)
    {
        l=L; r=R; mid=(l+r)>>1;
        if (l==r) v=s[l];
        else
        {
            lptr=new node(l, mid);
            rptr=new node(mid+1, r);
            v=lv+rv;
        }
    }
    void update(int pos, ll val)
    {
        if (l==r)
        {
            assert(l==pos);
            v=val;
            return;
        }
        
    }
};