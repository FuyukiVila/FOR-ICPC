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
//#define LOCAL
//#define PRIME

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

#ifdef PRIME

const int N = 1e7 + 100;
vector<int> minp(N);
vector<int> primes;
bitset<N> st;

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

#endif
#define int ll
const int inf = 1e12;
int a[55];
int b[55];
int dp[55][55];
int n, m1, m2;
int ans = inf;

int tmp = 0;

void check() {
    tmp++;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m2; j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m2; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= b[i]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - b[i]] + a[i]);
            }
        }
    }
    ans = min(ans, dp[n][m2]);
}


inline void init() {
    /*Init Here*/
}

void dfs(int now, int res = m1) {
    if (ans == 0) {
        cout << 0 << '\n';
        exit(0);
    }
    if (now == n) {
        b[n] = res;
        if (res < b[n - 1]) {
            return;
        }
        check();
        return;
    }
    for (int i = b[now - 1]; i <= res / (n - now + 1); i++) {
        b[now] = i;
        if (i < b[now - 1]) continue;
        dfs(now + 1, res - i);
    }
}

void idol_produce(int testCase) {
    /*Code Here*/
    cin >> n >> m1 >> m2;
    swap(m1, m2);
    if (m2 >= m1 * (n + 1)) {
        cout << 0 << '\n';
        return;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    dfs(1);
    cout << ans;
}

signed main() {
    GKD;
    init();
    int T = 1;
//    cin >> T;
    for (int i = 1; i <= T; i++) {
        idol_produce(i);
    }
    return 0;
}