// -
// livin' for the hope of it all

#include <iostream>
#include <cstring>
using namespace std;

const int N=100013;

struct node
{
    int h[N];
    
    node() { memset(h, -1, sizeof(h)); }
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

int main() { chash=new node(); }