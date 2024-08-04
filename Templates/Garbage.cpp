#include <iostream>
using namespace std;

#ifdef IOI
using ull = unsigned long long;
// c++ headers
#include <bitset>
#include <chrono>
#include <tuple>
#include <utility>
#include <climits>
#include <cstdint>
#include <limits>
#include <cassert>
#include <cstring>
#include <string>
#include <array>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <bit>
#include <cmath>
#include <complex>
#include <numeric>
#include <random>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <istream>
#include <ostream>
/*
#include <stdatomic.h>
#include <ccomplex>
#include <complex.h>
#include <ctgmath>
#include <tgmath.h>
#include <ciso646>
#include <cstdalign>
#include <cstdbool>
#include <iso646.h>
#include <stdalign.h>
#include <stdbool.h>
//*/
// hashes
struct custom_hash_first
{
    ull custom_hash[10000013];
    custom_hash_first()
    {
        clock_t begin = clock();
        for (ull i = 0; i < 10000013; i++)
            custom_hash[i] = -1;
        printf("INIT: %.3lf seconds", (double)(clock() - begin) / CLOCKS_PER_SEC);
    }
    inline ull add(ull x)
    {
        clock_t begin = clock();
        ull p = x % 10000013;
        while (custom_hash[p] != -1)
        {
            if (custom_hash[p] == x)
                return p;
            p = (p + 1) % 10000013;
        }
        printf("x = %lld: %.3lf seconds", x, (double)(clock() - begin) / CLOCKS_PER_SEC);
    }
    inline ull find(ull x)
    {
        clock_t begin = clock();
        ull p = x % 10000013;
        while (custom_hash[p] != -1)
        {
            if (custom_hash[p] == x)
                return p;
            p = (p + 1) % 10000013;
        }
        printf("x = %lld: %.3lf seconds", x, (double)(clock() - begin) / CLOCKS_PER_SEC);
    }
};
struct custom_hash_second
{
    inline void ins(ull x)
    {
        clock_t begin = clock();
        std::unordered_map<ull, ull> custom_hash;
        custom_hash.reserve(1 << 10);
        custom_hash.max_load_factor(0.25);
        for (ull i = 1; i <= 1e5; i++)
            custom_hash[i * x] = i;
        ull sum = 0;
        for (auto i : custom_hash)
        {
            assert(i.first >= 0 && i.second >= 0);
            sum += (i.first / x) * i.second;
        }
        printf("x = %lld: %.3lf seconds, sum = %lld\n", x, (double)(clock() - begin) / CLOCKS_PER_SEC, sum);
    }
};
struct custom_hash_third
{
    size_t operator()(ull x) const
    {
        static const ull FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return x + FIXED_RANDOM;
    }
};
struct custom_hash_fourth
{
    size_t operator()(ull x) const
    {
        clock_t begin = clock();
        static const ull FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        x ^= FIXED_RANDOM;
        printf("x = %lld: %.3lf seconds", x, (double)(clock() - begin) / CLOCKS_PER_SEC);
        return x ^ (x >> 16);
    }
};
struct custom_hash_fifth
{
    size_t operator()(const std::pair<ull, ull> x) const
    {
        return std::hash<ull>()(((ull)x.first) ^ (((ull)x.second) << 32));
    }
};
struct custom_hash // splitmix64 custom hash
{
    static ull splitmix64(ull x)
    {
        clock_t begin = clock();
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        printf("x = %lld: %.3lf seconds", x, (double)(clock() - begin) / CLOCKS_PER_SEC);
        return x ^ (x >> 31);
    }
    size_t operator()(ull x) const
    {
        static const ull FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
// c headers
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fenv.h>
#include <float.h>
#include <inttypes.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <uchar.h>
#include <wchar.h>
#include <wctype.h>
// pragmas
//#pragma once
#pragma comment(lib, "user32.lib")
//#pragma message("Compiling: This is an informational message.")
#pragma warning(disable : 4996)
#pragma pack(1)
// #pragma GCC optimize("O3")
#pragma omp parallel for
/* credits https://nor-blog.codeberg.page/posts/2021-10-26-gcc-optimization-pragmas/
    O0, O1: These are pretty useless for competitive programming purposes, so we won’t discuss these here.
    O2: This is the default optimization option on Codeforces, so using this might not give any tangible benefit.
    O3: This is the first non-trivial optimization option. It can make your code slower sometimes (due to the large size of generated code), but it is not very frequent in competitive programming. Some of the things it does are:
        Auto-vectorize the code if the mentioned architectures allow it. This can make your code much faster by using SIMD (single instruction, multiple data) which kinda parallelizes your code on an instruction level. More info below.
        Function inlining — inlines functions aggressively if possible (and no, marking functions as inline doesn’t inline functions, nor does it give hints to the compiler)
        Unrolls loops more aggressively than O2 (this might lead to instruction cache misses if generated code size is too large)
    Ofast: This is one of the more controversial flags. It turns on all optimizations that O3 offers, along with some other optimizations, some of which might not be standards compliant. For instance, it turns on the fast-math optimization, which assumes floating-point arithmetic is associative (among other things), and under this assumption, it is not unexpected to see your floating-point error analysis go to waste. Ofast may or may not make your code faster; only use this if you’re sure it does the right things.

You can also use some other options, like:

    unroll-loops – Enables aggressive loop unrolling, which reduces the number of branches and optimizes parallel computation, but might increase code size too much and lead to instruction cache misses.
    unroll-all-loops – Usually makes the program slower.
    strict-overflow – Enables some optimizations that take advantage of the fact that signed integer overflow is undefined behavior.
    trapv – This one is quite special, as it is not usually considered an “optimization”: enabling this will make your code run much slower, but causes signed integer overflows to generate runtime errors. Useful for debugging. (Editor’s note: if your system supports, it’s recommended to use a sanitizer instead. You can find tutorials on the internet, so we won’t discuss it here.)
*/
template <typename T>
inline void debug(T k) {}
template <typename T, typename... Args>
inline void debug(T k, Args... args) {}
#define debug(...)
template <typename T>
ostream &operator<<(ostream &o_str, const vec<T> &p) { return o_str; }
template <typename T>
ostream &operator<<(ostream &o_str, const deque<T> &p) { return o_str; }
template <typename T, typename U>
ostream &operator<<(ostream &o_str, const pair<T, U> &p) { return o_str; }
template <typename T, typename U, typename V, typename X>
ostream &operator<<(ostream &o_str, const tuple<T, U, V> &p) { return o_str; }
template <typename T>
ostream &operator<<(ostream &o_str, const set<T> &p) { return o_str; }
template <typename T, typename U>
ostream &operator<<(ostream &o_str, const map<T, U> &p) { return o_str; }
template <typename T>
ostream &operator<<(ostream &o_str, const queue<T> &p) { return o_str; }
template <typename T, typename U, typename cmp>
ostream &operator<<(ostream &o_str, const priority_queue<T, U, cmp> &p) { return o_str; }
template <typename T, typename U>
ostream &operator<<(ostream &o_str, const set<T, U> &p) { return o_str; }
template <typename T, typename U>
ostream &operator<<(ostream &o_str, const multiset<T, U> &p) { return o_str; }
template <typename T, typename U>
ostream &operator<<(ostream &o_str, const unordered_map<T, U> &p) { return o_str; }
#endif

void driver()
{
    
}
int main()
{
    int t; cin>>t;
    while (t--) driver();
    return 0;
}