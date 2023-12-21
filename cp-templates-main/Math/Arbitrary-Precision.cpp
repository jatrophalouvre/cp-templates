// https://codebreaker.xyz/problem/shortest
// to be completed

#include <iostream>
#include <cassert>
#define lx x.size()
#define ly y.size()
using namespace std;

using ll = long long;
const int N=100013;
string s;

string ADD(const string x, const string y)
{
    string ans;
    int nx[N]={0}, ny[N]={0};
    for (int a=0; a<lx; a++) nx[lx-1-a]=x[a]-'0';
    for (int a=0; a<ly; a++) ny[ly-1-a]=y[a]-'0';
    int lmax=(lx>ly?lx:ly);

    for (int a=0; a<lmax; a++)
    {
        nx[a]+=ny[a];
        nx[a+1]+=nx[a]/10;
        nx[a]%=10;
    }
    if (nx[lmax]) lmax++;
    for (int a=lmax-1; a>=0; a--) ans+=nx[a]+'0';
    return ans;
}
string SUB(const string x, const string y)
{
    string ans;
    int nx[N]={0}, ny[N]={0};
    for (int a=0; a<lx; a++) nx[lx-1-a]=x[a]-'0';
    for (int a=0; a<ly; a++) ny[ly-1-a]=y[a]-'0';
    int lmax=(lx>ly?lx:ly);

    for (int a=0; a<lmax; a++)
    {
        nx[a]-=ny[a];
        if (nx[a]<0)
        {
            nx[a]+=10;
            nx[a+1]--;
        }
    }
    while (!nx[--lmax] && lmax>0) ;
    lmax++;
    for (int a=lmax-1; a>=0; a--) ans+=nx[a]+'0';
    return ans;
}
string MUL(const string x, const string y)
{
    string ans;
    int nx[N]={0}, ny[N]={0}, nz[N]={0};
    for (int a=0; a<lx; a++) nx[lx-a]=x[a]-'0';
    for (int a=0; a<ly; a++) ny[ly-a]=y[a]-'0';
    for (int a=1; a<=lx; a++)
    {
        for (int b=1; b<=ly; b++)
        {
            nz[a+b-1]+=nx[a]*ny[b];
        }
    }
    for (int a=1; a<=lx+ly; a++)
    {
        for (int b=1; b<=ly; b++)
        {
            nz[a+1]+=nz[a]/10;
            nz[a]%=10;
        }
    }
    if (nz[lx+ly]) ans+=nz[lx+ly]+'0';
    for (int a=lx+ly-1; a>=1; a--) ans+=nz[a]+'0';
    return ans;
}
string DIV(const string x, const ll y)
{
    if (x=="0") return x;
    string ans;
    ll d=0, p=0;
    for (int a=0; a<x.size(); a++)
    {
        ans+=(d*10+x[a]-'0')/y+'0';
        d=(d*10+(x[a]-'0'))%y;
    }
    for (int a=0; a<ans.size(); a++)
    {
        if (ans[a]!='0')
        {
            p=a;
            break;
        }
    }
    return ans.substr(p);
}
bool LESS(const string x, const string y)
{
    if (x.size()!=y.size()) return x.size()<y.size();
    for (int a=0; a<x.size(); a++)
    {
        if (x[a]-'0'!=y[a]-'0') return x[a]-'0'<y[a]-'0';
    }
    return false;
}

int main()
{
    cin>>s;
    string l="1", r=s;
    while (ADD(l, "1")!=r)
    {
        string mid=DIV(ADD(l, r), 2);
        if (MUL(mid, mid)==s)
        {
            cout<<mid<<endl;
            return 0;
        }
        else if (LESS(MUL(mid, mid), s)) l=mid;
        else r=mid;
    }
    cout<<l<<endl;
    return 0;
}