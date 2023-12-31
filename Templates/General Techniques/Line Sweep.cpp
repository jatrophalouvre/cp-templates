// https://codebreaker.xyz/problem/globalwarming
// to be reviewed

#include <bits/stdc++.h>
#define int long long
#define fir first
#define sec second
using namespace std;

using PII = pair<int, int>;
const int N=100013;
int n, ans=1;
int h[N];
PII s[N];
int cur=2;

signed main()
{
	cin>>n;
	for (int a=0; a<n; a++)
	{
		cin>>h[a];
		s[a]={h[a], a};
	}
	sort(s, s+n);
	
	for (int a=0; a<n; a++)
	{
		if (s[a].sec==0 || h[s[a].sec-1]<s[a].fir) cur--;
		else if (h[s[a].sec-1]>s[a].fir) cur++;
		if (s[a].sec==n-1 || h[s[a].sec+1]<s[a].fir) cur--;
		else if (h[s[a].sec+1]>s[a].fir) cur++;
		if (a==n-1 || s[a].fir!=s[a+1].fir) ans=max(ans, cur/2);
	}
	cout<<ans<<endl;
	return 0;
}