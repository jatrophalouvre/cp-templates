// https://www.luogu.com.cn/problem/P3375
#include <iostream>
using namespace std;

const int N=2000013;
int n, m;
int pi[N];
string s, s1, s2;
int ans=0;

void kmp()
{
    pi[0]=0;
    for (int i=1; i<s.size(); i++)
    {
        int j=pi[i-1];
        while (j && s[j]!=s[i]) j=pi[j-1];
        if (s[i]==s[j]) j++;
        pi[i]=j;
    }
}

int main()
{
    cin>>s1>>s2;
    n=s1.size(); m=s2.size();
    s=s2+'@'+s1;
    kmp();
    for (int i=2*m; i<s.size(); i++)
    {
        if (pi[i]==m)
        {
            cout<<i-2*m+1<<endl;
            ans++;
        }
    }
    for (int i=0; i<m; i++) cout<<pi[i]<<' '; cout<<endl;
    return 0;
}