// -
#include <iostream>
#define int long long
using namespace std;

const int N=100013;

struct CHASH
{
    int h[N];
    
    CHASH() { fill(h, h+N, -1); }
    int add(int x)
    {
        int p=x%N;
        while (h[p]!=-1)
        {
            if (h[p]==x) return p;
            p=(p+1)%N;
        }
    }
    int find(int x)
    {
        int p=x%N;
        while (h[p]!=-1)
        {
            if (h[p]==x) return p;
            p=(p+1)%N;
        }
    }
} *chash;

signed main() { chash=new CHASH(); }