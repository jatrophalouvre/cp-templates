// https://www.luogu.com.cn/problem/P1032
// livin' for the hope of it all

#include <iostream>
#include <unordered_map>
#include <vector>
#define lx x.size()
#define ly y.size()
using namespace std;

using ll = long long;
const int N=1013;

struct node
{
    const ll mod[2]={1000000007, 1000000009};
    ll pwr[2][N];
    unordered_map<string, vector<vector<ll>>> h;
    
    node()
    {
        pwr[0][0]=pwr[1][0]=1;
        for (int a=1; a<N; a++)
        {
            pwr[0][a]=(pwr[0][a-1]*131)%mod[0];
            pwr[1][a]=(pwr[1][a-1]*131)%mod[1];
        }
    }
    void insert(string x)
    {
        h[x].resize(2, vector<ll>(lx+1));
        h[x][0][0]=h[x][1][0]=0;
        for (int a=0; a<lx; a++)
        {
            h[x][0][a+1]=(h[x][0][a]+x[a]*pwr[0][a])%mod[0];
            h[x][1][a+1]=(h[x][1][a]+x[a]*pwr[1][a])%mod[1];
        }
    }
    vector<int> query(string x, string y)
    {
        vector<int> ans;
        for (int a=0; a+ly-1<lx; a++) if (check(a, x, y)) ans.push_back(a);
        return ans;
    }
    bool check(int pos, string x, string y)
    {
        bool t1=calc(0, h[x][0][pos+ly]-h[x][0][pos]) == calc(0, h[y][0][ly]*pwr[0][pos]);
        bool t2=calc(1, h[x][1][pos+ly]-h[x][1][pos]) == calc(1, h[y][1][ly]*pwr[1][pos]);
        return t1 && t2;
    }
    ll calc(int i, ll x) { return (x%mod[i]+mod[i])%mod[i]; }
} *rk;

int main()
{
    rk=new node();
    string x, y; cin>>x>>y;
    rk->insert(x); rk->insert(y);
    
    vector<int> ans=rk->query(x, y);
    cout<<ans.size()<<endl;
    for (auto a:ans) cout<<a<<' ';
    cout<<endl;
    return 0;
}