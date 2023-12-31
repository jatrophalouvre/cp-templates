// to be reviewed

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=1000013;
int n, m;
int kmp[N];
string s, s1, s2;

void init()
{
    kmp[0]=0;
    for (int a=1; a<m; a++)
    {
        int b=kmp[a-1];
        while (b && s2[b]!=s2[a]) b=kmp[b-1];
        if (s2[a]==s2[b]) b++;
        kmp[a]=b;
    }
}

signed main()
{
    cin>>s1>>s2;
    n=s1.size(); m=s2.size();
    init();
    int b=0;
    for (int a=0; a<n; a++)
    {
        while (b && s2[b]!=s1[a]) b=kmp[b-1];
        if (s2[b]==s1[a]) b++;
        if (b==m)
        {
            cout<<a-b+1<<' ';
            b=kmp[b-1];
        }
    }
    return 0;
}