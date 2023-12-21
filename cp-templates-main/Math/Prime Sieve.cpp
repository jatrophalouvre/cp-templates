// https://codebreaker.xyz/problem/nprime
// livin' for the hope of it all

#include <iostream>
#include <vector>
using namespace std;

const int N=1000013;
int lp[N]={0};
vector<int> p;

void init()
{
    for (int a=2; a<=N; a++)
    {
        if (lp[a]==0)
        {
            lp[a]=a;
            p.push_back(a);
        }
        for (int b=0; a*p[b]<=N; b++)
        {
            lp[a*p[b]]=p[b];
            if (p[b]==lp[a]) break;
        }
    }
}

int main()
{
    init();
    int n; cin>>n;
    cout<<p[n-1]<<endl;
    return 0;
}