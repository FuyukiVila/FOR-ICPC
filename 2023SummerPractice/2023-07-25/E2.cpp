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
template<class T>
using uset = unordered_set<T, T>;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;

template<typename T>
inline constexpr T qpow(T a, T n, T mod) {
    T ans = 1;
    while (n) {
        if (n & 1) ans *= a;
        n >>= 1;
        a *= a;
        if (mod > 0) {
            ans %= mod;
            a %= mod;
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

#define int long long
const int MAXN = 3e4 + 6;
int a[MAXN], c[MAXN], _a[MAXN];
int dp[4000][4000];
const int mod = 1e9 + 7;

auto genshin_start() {
    memset(dp, 0, sizeof(dp));
    memset(c, 0, sizeof(c));
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> _a[i];
    }
    sort(_a + 1, _a + 1 + n);
    int cnt = 1;
    for (int i = 1; i <= n; i++) {
        if (_a[i] != _a[i - 1]) {
            a[i] = cnt++;
            c[i] = c[i - 1] + 1;
        } else {
            a[i] = cnt;
            c[i] = c[i - 1];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (c[i] == c[i - 1]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                if (j == 1) {
                    dp[i][j] = c[i];
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                    dp[i][j] %= mod;
                }
            }
        }
        dp[i][i] = dp[i][i - 1];
    }
    for (int i = 1; i <= n; i++) {
        cout << dp[n][i] % mod << '\n';
    }
}

signed main() {
    GKD;
    auto T{1};
    cin >> T;
    while (T--) genshin_start();
    return 0;
}