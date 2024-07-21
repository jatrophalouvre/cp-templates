// -
#include <iostream>
#include <chrono>
#include <random>
using namespace std;
using ll=long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct WRONG
{
    int main() {}
} *wrong;

struct CORRECT
{
    int main() {}
} *correct;

int main()
{
    for (int _=0; _<100013; _++)
    {
        wrong=new WRONG; correct=new CORRECT;
        ll out_wrong=wrong->main();
        ll out_correct=correct->main();
        if (out_wrong!=out_correct)
        {
            cout<<endl;
            cout<<"WRONG: "<<out_wrong<<endl;
            cout<<"CORRECT: "<<out_correct<<endl;
            return 0;
        }
        cerr<<"PASSED "<<_<<endl;
    }
    cout<<"PASSED ALL"<<endl;
    return 0;
}