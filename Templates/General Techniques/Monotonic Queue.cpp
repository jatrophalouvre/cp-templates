// https://www.luogu.com.cn/problem/P1886
// livin' for the hope of it all

#include <iostream>
#include <queue>
using namespace std;

using ll = long long;
const int N=100013;
int n, m;
ll s[N];

int main()
{
    cin>>n>>m;
    for (int a=0; a<n; a++) cin>>s[a];
    
    deque<int> q; q.push_back(0);
    for (int a=1; a<n; a++)
    {
        while (q.size() && q.front()<=a-m) q.pop_front();
        while (q.size() && s[q.back()]>s[a]) q.pop_back();
        q.push_back(a);
        if (a+1>=m) cout<<s[q.front()]<<' ';
    }
    cout<<endl;
    return 0;
}