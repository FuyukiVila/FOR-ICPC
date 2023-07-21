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
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
const ll mod = 1e9 + 7;

template<typename T>
inline constexpr T qpow(T a, T n) {
    T ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        n >>= 1;
        a = (a * a) % mod;
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

ll inv[1005];

void init() {
    inv[1] = 1;
    for (ll i = 2; i <= 1e3 + 5; i++) {
        inv[i] = qpow(i, mod - 2);
    }
}

int choose(int n, int m) {
    if (n < m)return 0;
    int res = 1;
    for (int i = n; i > n - m; i--) {
        res = res * i % mod;
    }
    for (int i = 1; i <= m; i++) {
        res = res * inv[i] % mod;
    }
    return res % mod;
}

int out[1005];
bitset<1005> e[1005];
int n, m;

auto genshin_start() {
    int ans = 0;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        out[i] = 0;
        e[i].reset();
    }

    for (int i = 1; i <= m; i++) {
        int v, u;
        cin >> v >> u;
        e[v][u] = true;
        e[u][v] = true;
        out[v]++;
        out[u]++;
    }
//    for (int i = 1; i <= n; i++) {
//        dfs(i, i);
//    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int cnt = (e[i] & e[j]).count();
            if (cnt >= 4) {
                if (out[i] >= 6) {
                    ans = ans + choose(cnt, 4) * choose(out[i] - 4 - e[i][j], 2) % mod;
                    ans = ans % mod;
                }
                if (out[j] >= 6) {
                    ans = ans + choose(cnt, 4) * choose(out[j] - 4 - e[j][i], 2) % mod;
                    ans = ans % mod;
                }
            }
        }
    }
    cout << ans << '\n';
}

signed main() {
    GKD;
    init();
    auto T{1};
    cin >> T;
    while (T--) genshin_start();
    return 0;
}