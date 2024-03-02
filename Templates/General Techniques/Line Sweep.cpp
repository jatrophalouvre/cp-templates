// https://codebreaker.xyz/problem/globalwarming
#include <iostream>
#include <algorithm>
#define int long long
#define fir first
#define sec second
using namespace std;

const int N=100013;
int n, ans=1;
int h[N];
pair<int, int> s[N];
int cur=2;

signed main()
{
	cin>>n;
    for (int i=0; i<n; i++)
	{
		cin>>h[i];
		s[i]={h[i], i};
	}
	sort(s, s+n);
	
    for (int i=0; i<n; i++)
	{
		if (s[i].sec==0 || h[s[i].sec-1]<s[i].fir) cur--;
		else if (h[s[i].sec-1]>s[i].fir) cur++;
		if (s[i].sec==n-1 || h[s[i].sec+1]<s[i].fir) cur--;
		else if (h[s[i].sec+1]>s[i].fir) cur++;
		if (i==n-1 || s[i].fir!=s[i+1].fir) ans=max(ans, cur/2);
	}
	cout<<ans<<endl;
	return 0;
}