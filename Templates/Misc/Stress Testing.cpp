// -
#include <iostream>
#include <chrono>
#include <random>
#define int long long
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct WRONG
{
    signed main() {}
} *wrong;

struct CORRECT
{
    signed main() {}
} *correct;

signed main()
{
    for (int _=0; _<100013; _++)
    {
        wrong=new WRONG; correct=new CORRECT;
        int out_wrong=wrong->main();
        int out_correct=correct->main();
        if (out_wrong!=out_correct)
        {
            cerr<<endl;
            cerr<<"WRONG: "<<out_wrong<<endl;
            cerr<<"CORRECT: "<<out_correct<<endl;
            return 0;
        }
        cerr<<"PASSED "<<_<<endl;
    }
    cerr<<"PASSED ALL"<<endl;
    return 0;
}