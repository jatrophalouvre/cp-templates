// -
#include <iostream>
#include <chrono>
using namespace std;
using ll=long long;
using ull=unsigned ll;

const int N=1000013;

struct CH
{
    static ull splitmix64(ull x)
    {
        x+=0x9e3779b97f4a7c15;
        x=(x^(x>>30))*0xbf58476d1ce4e5b9;
        x=(x^(x>>27))*0x94d049bb133111eb;
        return x^(x>>31);
    }
    size_t operator()(ull x) const
    {
        static const ull FR=chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x+FR);
    }
};

int main() {}