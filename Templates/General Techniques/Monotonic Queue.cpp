// https://www.luogu.com.cn/problem/P1886
#include <iostream>
#include <queue>
#define int long long
using namespace std;

const int N=100013;
int n, m;
int s[N];

signed main()
{
    cin>>n>>m;
    for (int i=0; i<n; i++) cin>>s[i];
    
    deque<int> q; q.push_back(0);
    for (int i=1; i<n; i++)
    {
        while (q.size() && q.front()<=i-m) q.pop_front();
        while (q.size() && s[q.back()]>s[i]) q.pop_back();
        q.push_back(i);
        if (i+1>=m) cout<<s[q.front()]<<' ';
    }
    cout<<endl;
    return 0;
}