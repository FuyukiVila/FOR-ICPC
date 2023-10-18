#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

#define dbg(x...) \
    do { \
        std::cout << #x << " -> "; \
        err(x); \
    } while (0)

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
template<typename T>
using umap = unordered_map<T, T>;
template<typename T>
using uset = unordered_set<T, T>;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
const ll mod = 1e9 + 7;

inline constexpr ll qpow(ll _a, ll _n, ll _mod = mod) {
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
int minp[N];
vector<int> primes;
bool st[N];

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

std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_int_distribution<ll> ranint(1, 1e18);

//玩原神导致的
ll dp[1000005][4][4];

//第i位的i，和i-1的情况数
// 0 - 0 1 - 1 2 - 2 3 - *
void genshin_start() {
    string s;
    cin >> s;
    if (s.size() == 1) {
        if (s[0] == '2' || s[0] == '1') {
            cout << 0 << '\n';
        } else if (s[0] == '0' || s[0] == '*') {
            cout << 1 << '\n';
        } else {
            cout << 2 << '\n';
        }
        return;
    }
    if (s[0] == '1' && s[1] == '*') {
        dp[1][1][3] = 1;
    } else if (s[0] == '*' && s[1] == '1') {
        dp[1][3][1] = 1;
    } else if (s[0] == '*' && s[1] == '*') {
        dp[1][3][3] = 1;
    } else if (s[0] == '0' && s[1] == '0') {
        dp[1][0][0] = 1;
    } else if (s[0] == '*' && s[1] == '2') {
        dp[1][3][2] = 1;
    } else if (s[0] == '?') {
        if (s[1] == '*') {
            dp[1][1][3] = 1;
            dp[1][3][3] = 1;
        } else if (s[1] == '1') {
            dp[1][3][1] = 1;
            dp[1][0][1] = 1;
        } else if (s[1] == '0') {
            dp[1][0][0] = 1;
        } else if (s[1] == '2') {
            dp[1][3][2] = 1;
        }
    } else if (s[1] == '?') {
        if (s[0] == '*') {
            dp[1][3][3] = 1;
            dp[1][3][1] = 1;
            dp[1][3][2] = 1;
        } else if (s[0] == '1') {
            dp[1][1][3] = 1;
        } else if (s[0] == '0') {
            dp[1][0][0] = 1;
        }
    }
    if (s[0] == '?' && s[1] == '?') {
        dp[1][0][0] = 1;
        dp[1][0][1] = 1;
        dp[1][0][3] = 1;
        dp[1][1][3] = 1;
        dp[1][3][1] = 1;
        dp[1][3][2] = 1;
        dp[1][3][3] = 1;
    }
    for (int i = 2; i < s.size(); i++) {
        if (s[i] == '1') {
            dp[i][0][1] = (dp[i - 1][0][0] + dp[i - 1][1][0]) % mod;
            dp[i][1][1] = dp[i - 1][3][1] % mod;
            dp[i][3][1] = (dp[i - 1][3][3] + dp[i - 1][1][3] + dp[i - 1][2][3]) % mod;
        } else if (s[i] == '2') {
            dp[i][3][2] = (dp[i - 1][3][3] + dp[i - 1][1][3] + dp[i - 1][2][3]) % mod;
        } else if (s[i] == '0') {
            dp[i][0][0] = (dp[i - 1][0][0] + dp[i - 1][1][0]) % mod;
            dp[i][1][0] = dp[i - 1][3][1] % mod;
        } else if (s[i] == '*') {
            dp[i][1][3] = (dp[i - 1][0][1] + dp[i - 1][1][1]) % mod;
            dp[i][2][3] = dp[i - 1][3][2] % mod;
            dp[i][3][3] = (dp[i - 1][3][3] + dp[i - 1][1][3] + dp[i - 1][2][3]) % mod;
        } else {
            dp[i][0][1] = (dp[i - 1][0][0] + dp[i - 1][1][0]) % mod;
            dp[i][1][1] = dp[i - 1][3][1] % mod;
            dp[i][3][1] = (dp[i - 1][3][3] + dp[i - 1][1][3] + dp[i - 1][2][3]) % mod;
            dp[i][3][2] = (dp[i - 1][3][3] + dp[i - 1][1][3] + dp[i - 1][2][3]) % mod;
            dp[i][0][0] = (dp[i - 1][0][0] + dp[i - 1][1][0]) % mod;
            dp[i][1][0] = dp[i - 1][3][1] % mod;
            dp[i][1][3] = (dp[i - 1][0][1] + dp[i - 1][1][1]) % mod;
            dp[i][2][3] = dp[i - 1][3][2] % mod;
            dp[i][3][3] = (dp[i - 1][3][3] + dp[i - 1][1][3] + dp[i - 1][2][3]) % mod;
        }
    }
    ll ans = 0;
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            if (j == 2)continue;
            if (j == 1 && i != 3)continue;
            ans += dp[s.size() - 1][i][j];
            ans %= mod;
        }
    }
    cout << ans << '\n';
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}