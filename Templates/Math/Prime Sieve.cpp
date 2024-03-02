// https://codebreaker.xyz/problem/nprime
#include <iostream>
#include <vector>
#define int long long
using namespace std;

const int N=1000013;
int lp[N]={0};
vector<int> p;

void init()
{
    for (int i=2; i<=N; i++)
    {
        if (lp[i]==0)
        {
            lp[i]=i;
            p.push_back(i);
        }
        for (int j=0; i*p[j]<=N; j++)
        {
            lp[i*p[j]]=p[j];
            if (p[j]==lp[i]) break;
        }
    }
}

signed main()
{
    init();
    int n; cin>>n;
    cout<<p[n-1]<<endl;
    return 0;
}