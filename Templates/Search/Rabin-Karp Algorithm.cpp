// https://www.luogu.com.cn/problem/P1032
// livin' for the hope of it all

#include <iostream>
#include <unordered_map>
#include <vector>
#define int long long
#define lx x.size()
#define ly y.size()
using namespace std;

const int N=1013;

struct RK
{
    const int mod[2]={1000000007, 1000000009};
    int pwr[2][N];
    unordered_map<string, vector<vector<int>>> h;
    
    RK()
    {
        pwr[0][0]=pwr[1][0]=1;
        for (int i=1; i<N; i++)
        {
            pwr[0][i]=(pwr[0][i-1]*131)%mod[0];
            pwr[1][i]=(pwr[1][i-1]*131)%mod[1];
        }
    }
    void insert(string x)
    {
        h[x].resize(2, vector<int>(lx+1));
        h[x][0][0]=h[x][1][0]=0;
        for (int i=0; i<lx; i++)
        {
            h[x][0][i+1]=(h[x][0][i]+x[i]*pwr[0][i])%mod[0];
            h[x][1][i+1]=(h[x][1][i]+x[i]*pwr[1][i])%mod[1];
        }
    }
    vector<int> query(string x, string y)
    {
        vector<int> ans;
        for (int i=0; i+ly-1<lx; i++) if (check(i, x, y)) ans.push_back(i);
        return ans;
    }
    bool check(int pos, string x, string y)
    {
        bool t1=calc(0, h[x][0][pos+ly]-h[x][0][pos]) == calc(0, h[y][0][ly]*pwr[0][pos]);
        bool t2=calc(1, h[x][1][pos+ly]-h[x][1][pos]) == calc(1, h[y][1][ly]*pwr[1][pos]);
        return t1 && t2;
    }
    int calc(int i, int x) { return (x%mod[i]+mod[i])%mod[i]; }
} *rk;

signed main()
{
    rk=new RK();
    string x, y; cin>>x>>y;
    rk->insert(x); rk->insert(y);
    
    vector<int> ans=rk->query(x, y);
    cout<<ans.size()<<endl;
    for (auto i:ans) cout<<i<<' ';
    cout<<endl;
    return 0;
}