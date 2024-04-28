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
#define LOCAL

#include <bits/stdc++.h>

#ifdef LOCAL

#define dbg(x...) \
    do { \
        std::cout << #x << " -> "; \
        err(x); \
    } while (0);
#else
#define dbg(x...) 114514;
#endif

void err() {
    std::cout << std::endl;
}

template<class T, class... Ts>
void err(T arg, Ts &... args) {
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
        if (_n & 1) ans *= _a;
        _n >>= 1;
        _a *= _a;
        if (_mod > 0) {
            ans %= _mod;
            _a %= _mod;
        }
    }
    return ans;
}

constexpr int N = 1e7 + 100;
vector<int> minp(N);
vector<int> primes;
bitset<N> st;

void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) minp[i] = i, primes.emplace_back(i);
        for (int j = 0; primes[j] * i <= n; j++) {
            int t = primes[j] * i;
            st[t] = true;
            minp[t] = primes[j];
            if (i % primes[j] == 0) break;
        }
    }
}

//为什么要演奏春日影！
struct answer {
    int type, line;

    answer(int _type, int _line) : line(_line) {
        if (_type == 0) {
            type = 2;
        } else {
            type = 1;
        }
    }
};

void haruhikage_start(int testCase) {
    int n;
    cin >> n;
    vector<answer> ans;
    vector<vector<int> > a(n + 1, vector<int>(n + 1));
    for (int i = 1, k = n; i <= n; i++, k--) {
        for (int j = 1; j <= n; j++) {
            a[k][j] = j;
        }
        ans.emplace_back(1, k);
        for (int j = 1; j <= n; j++) {
            a[j][k] = j;
        }
        ans.emplace_back(0, k);
    }
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            sum += a[i][j];
        }
    }
    cout << sum << ' ' << n * 2 << '\n';
    for (auto const &[t, i]: ans) {
        cout << t << ' ' << i << ' ';
        for (int i = 1; i <= n; i++) {
            cout << i << " \n"[i == n];
        }
    }
//    for (int i = 1; i <= n; i++) {
//        for (int j = 1; j <= n; j++) {
//            cerr << a[i][j] << " \n"[j == n];
//        }
//    }
}

signed main() {
    GKD;
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        haruhikage_start(i);
    }
    return 0;
}

