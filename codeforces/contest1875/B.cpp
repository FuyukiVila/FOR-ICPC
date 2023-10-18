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
const int mod = 0;

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
void genshin_start() {
    int n, m;
    cin >> n >> m;
    if (n % m == 0) {
        cout << 0 << '\n';
    } else {
        ll a = n % m / __gcd(m, n);
        ll b = m / __gcd(m, n);
        ll _b = b;
        while (_b != 1) {
            if (_b % 2 != 0) {
                cout << -1 << '\n';
                return;
            }
            _b /= 2;
        }
        ll ans = 0;
        ll tmp = 1;
        ll k = 2;
        while (a != 0) {
            if (a < b / k) {
                k *= 2;
                tmp ++;
                continue;
            }
            a -= b / k;
            if (m % k != 0) {
                cout << -1 << '\n';
                return;
            }
            ans += m / k * (qpow(2, tmp) - 1);
            k *= 2;
            tmp ++;
        }
        cout << ans << '\n';
    }
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) genshin_start();
    return 0;
}