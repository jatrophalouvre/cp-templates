// -
#include <iostream>
using namespace std;
using ll=long long;

const int N=1000013;

struct CHASH
{
    int h[N];
    
    CHASH()
    {
        for (int i=0; i<N; i++) h[i]=-1;
    }
    int add(ll x)
    {
        int p=x%N;
        while (h[p]!=-1)
        {
            if (h[p]==x) return p;
            p=(p+1)%N;
        }
    }
    int find(ll x)
    {
        int p=x%N;
        while (h[p]!=-1)
        {
            if (h[p]==x) return p;
            p=(p+1)%N;
        }
    }
} *chash;

int main() { chash=new CHASH(); }