/*
  ______                 _    _  __      ___ _
 |  ____|               | |  (_) \ \    / (_) |
 | |__ _   _ _   _ _   _| | ___   \ \  / / _| | __ _
 |  __| | | | | | | | | | |/ / |   \ \/ / | | |/ _` |
 | |  | |_| | |_| | |_| |   <| |    \  /  | | | (_| |
 |_|   \__,_|\__, |\__,_|_|\_\_|     \/   |_|_|\__,_|
              __/ |
             |___/
*/

#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))
#define cpy(a, b) memcpy(a, b, sizeof(a))

#include <bits/stdc++.h>

#ifdef LOCAL

#define dbg(x...)                                                              \
    do {                                                                       \
        std::cout << #x << " -> ";                                             \
        err(x);                                                                \
    } while (0);
#else
#define dbg(x...) 114514;
#endif

void err() { std::cout << std::endl; }

template<class T, class... Ts>
void err(T arg, Ts &...args) {
    std::cout << arg << ' ';
    err(args...);
}

using namespace std;
using ll = long long;
using ull = unsigned long long;
const int INF = 0x3f3f3f3f;
ll mod = 0;

inline ll qpow(ll _a, ll _n, ll _mod = mod) {
    ll ans = 1;
    while (_n) {
        if (_n & 1)
            ans *= _a;
        _n >>= 1;
        _a *= _a;
        if (_mod > 0) {
            ans %= _mod;
            _a %= _mod;
        }
    }
    return ans;
}

constexpr int _N = 1e7 + 100;
vector<int> minp(_N);
vector<int> primes;
bitset<_N> st;

void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i])
            minp[i] = i, primes.emplace_back(i);
        for (int j = 0; primes[j] * i <= n; j++) {
            int t = primes[j] * i;
            st[t] = true;
            minp[t] = primes[j];
            if (i % primes[j] == 0)
                break;
        }
    }
}

inline void init() {
    /*Init Here*/
}

void idol_produce(int testCase) {
    /*Code Here*/
    mod = 1000003;
    int n;
    vector<int> a{1, 1}, b;
    map<int, vector<int> > ans;
    for (int i = 3; i <= 30; i++) {
        b.emplace_back(a[0]);
        for (int j = 1; j < a.size(); j++) {
            b.emplace_back(a[j] + a[j - 1]);
            if ((a[j] + a[j - 1]) % 2 == 0) {
                ans[i].emplace_back(a[j] + a[j - 1]);
            }
        }
        b.emplace_back(a.back());
        a = b;
        b.clear();
    }
    filebuf fb;
    fb.open("out.txt", iostream::out);
    iostream out(&fb);
    for (auto const &x: ans) {
        out << x.first << " : ";
        for (auto const &y: x.second) {
            out << y << " ";
        }
        out << "sum : " << accumulate(x.second.begin(), x.second.end(), 0) << ' ';
        out << "cnt : " << x.second.size() << '\n';
        out << '\n';
    }
}

signed main() {
    GKD;
    init();
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        idol_produce(i);
    }
    return 0;
}
