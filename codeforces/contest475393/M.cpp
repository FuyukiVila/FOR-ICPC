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
using i64 = long long;
using ull = unsigned long long;
template<typename T>
using umap = unordered_map<T, T>;
template<class T>
using uset = unordered_set<T, T>;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
const ll mod = 998244353;

inline constexpr ll qpow(ll a, ll n) {
    ll ans = 1;
    while (n) {
        if (n & 1) ans = ans * a % mod;
        n >>= 1;
        a = a * a % mod;
    }
    return ans % mod;
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

ll fac[50005];
ll inv[50005];

auto genshin_start() {
    int n, m;
    cin >> n >> m;
    fac[0] = 1;
    for (int i = 1; i <= 50000; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    inv[50000] = qpow(fac[50000], mod - 2);
    for (int i = 50000; i >= 0; i--) {
        inv[i - 1] = inv[i] * i % mod;
    }
    vector<int> a(n + 1);
    map<ll, ll> cnt;
    int maxn = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
        maxn = max(maxn, a[i]);
    }
//    cout << fac[10] * inv[10] % mod << '\n';
    for (int i = 1; i <= m; i++) {
        ll ans = 1;
        if (i < maxn) {
            cout << 0 << '\n';
        } else {
            for (auto const &[x, y]: cnt) {
                ans = ans * qpow((fac[i] * inv[i - x] % mod) * inv[x] % mod, y) % mod;
            }
            cout << ans << '\n';
        }
    }
}

signed main() {
    GKD;
    auto T{1};
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}