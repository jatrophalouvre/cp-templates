// https://www.luogu.com.cn/problem/P3372
// livin' for the hope of it all

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=100013;
int n, m;
int s[N];

struct node
{
    int B, l[N], r[N];
    int v[N]={0}, lazy[N]={0};
    
    node()
    {
        B=sqrt(n);
        for (int b=0; b<=(n-1)/B; b++)
        {
            l[b]=b*B;
            r[b]=min((b+1)*B-1, n-1);
            for (int a=l[b]; a<=r[b]; a++) v[b]+=s[a];
        }
    }
    void update(int pos, int val)
    {
        v[pos/B]+=val-s[pos];
        s[pos]+=val-s[pos];
    }
    void update(int x, int y, int val)
    {
        int bx=x/B, by=y/B;
        if (bx==by)
        {
            for (int a=x; a<=y; a++) s[a]+=val;
            v[bx]+=val*(y-x+1);
        }
        else
        {
            for (int b=bx+1; b<=by-1; b++) lazy[b]+=val;
            for (int a=x; a<=r[bx]; a++) s[a]+=val;
            v[bx]+=val*(r[bx]-x+1);
            for (int a=l[by]; a<=y; a++) s[a]+=val;
            v[by]+=val*(y-l[by]+1);
        }
    }
    int query(int pos) { return s[pos]+lazy[pos/B]; }
    int query(int x, int y)
    {
        int ans=0;
        int bx=x/B, by=y/B;
        if (bx==by) for (int a=x; a<=y; a++) ans+=s[a]+lazy[bx];
        else
        {
            for (int b=bx+1; b<=by-1; b++) ans+=v[b]+lazy[b]*(r[b]-l[b]+1);
            for (int a=x; a<=r[bx]; a++) ans+=s[a]+lazy[bx];
            for (int a=l[by]; a<=y; a++) ans+=s[a]+lazy[by];
        }
        return ans;
    }
} *sqrtd;

signed main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++) cin>>s[a];
    
    sqrtd=new node();
    while (m--)
    {
        int t; cin>>t;
        if (t==1)
        {
            int l, r, val; cin>>l>>r>>val;
            sqrtd->update(l, r, val);
        }
        else
        {
            int l, r; cin>>l>>r;
            cout<<sqrtd->query(l, r)<<endl;
        }
    }
    return 0;
}