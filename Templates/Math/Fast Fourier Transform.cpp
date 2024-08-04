// https://www.luogu.com.cn/problem/P3803
#include <iostream>
#include <cmath>
using namespace std;
using ld=long double;

const int N=10000013;
const double PI=acos(-1.0);
int n, m;
int lim=1, l=0, r[N];

struct complex
{
    double x, y;
    complex operator+(const complex a) const { return complex({x+a.x, y+a.y}); }
    complex operator-(const complex a) const { return complex({x-a.x, y-a.y}); }
    complex operator*(const complex a) const { return complex{x*a.x-y*a.y, x*a.y+y*a.x}; }
} a[N], b[N];

void fft(complex *z, int t)
{
    for (int i=0; i<lim; i++) if (i<r[i]) swap(z[i], z[r[i]]);
    for (int mid=1; mid<lim; mid<<=1)
    {
        complex root={cos(PI/mid), t*sin(PI/mid)};
        for (int R=mid<<1, i=0; i<lim; i+=R)
        {
            complex w={1, 0};
            for (int j=0; j<mid; j++, w=w*root)
            {
                complex x=z[i+j], y=w*z[i+j+mid];
                z[i+j]=x+y;
                z[i+j+mid]=x-y;
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    for (int i=0; i<=n; i++) cin>>a[i].x;
    for (int i=0; i<=m; i++) cin>>b[i].x;
    
    while (lim<=n+m)
    {
        lim<<=1;
        l++;
    }
    for (int i=0; i<lim; i++) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
    fft(a, 1);
    fft(b, 1);
    for (int i=0; i<=lim; i++) a[i]=a[i]*b[i];
    fft(a, -1);
    
    for (int i=0; i<=n+m; i++) cout<<int(a[i].x/lim +0.5)<<' '; cout<<endl;
    return 0;
}