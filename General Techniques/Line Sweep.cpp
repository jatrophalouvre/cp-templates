// https://codebreaker.xyz/problem/globalwarming
// to be reviewed

#include <iostream>
#include <algorithm>
#include <utility>
#define x first
#define y second
using namespace std;

using PII = pair<int, int>;
const int N=100013;
int n, ans=1;
int h[N];
PII s[N];
int cur=2;

int main()
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
		if (s[a].y==0 || h[s[a].y-1]<s[a].x) cur--;
		else if (h[s[a].y-1]>s[a].x) cur++;
		if (s[a].y==n-1 || h[s[a].y+1]<s[a].x) cur--;
		else if (h[s[a].y+1]>s[a].x) cur++;
		if (a==n-1 || s[a].x!=s[a+1].x) ans=max(ans, cur/2);
	}
	cout<<ans<<endl;
	return 0;
}