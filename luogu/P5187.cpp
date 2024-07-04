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

//constexpr int _N = 1e7 + 100;
//vector<int> minp(_N);
//vector<int> primes;
//bitset<_N> st;
//
//void get_primes(int n) {
//    for (int i = 2; i <= n; i++) {
//        if (!st[i])
//            minp[i] = i, primes.emplace_back(i);
//        for (int j = 0; primes[j] * i <= n; j++) {
//            int t = primes[j] * i;
//            st[t] = true;
//            minp[t] = primes[j];
//            if (i % primes[j] == 0)
//                break;
//        }
//    }
//}

inline void init() {
    /*Init Here*/
}

void idol_produce(int testCase) {
    /*Code Here*/
    mod = 10301;
    int n, a, b;
    cin >> n >> a >> b;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i - 1; j >= 1; j--) {
            dp[i][j] = (dp[i][j + 1] + dp[i - j][j]) % mod;
        }
    }
    int ans = 0;
    for (int i = a; i <= n - b; i++) {
        ans = (ans + ((dp[i][a] - dp[i - 1][a] + mod) % mod)
                     * (dp[n - i][b] % mod)) % mod;
    }
    cout << ans;
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
