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
using i64 = long long;
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

ll mod = 998244353;
ll fac[200005];

void init() {
    fac[0] = 1;
    for (int i = 1; i <= 2e5; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
}

auto genshin_start() {
    string s;
    cin >> s;
    vector<pair<int, char>> v;
    pair<int, char> tmp{1, s[0]};
    for (int i = 1; i <= s.size(); i++) {
        if (tmp.second == s[i]) {
            tmp.first++;
        } else {
            v.emplace_back(tmp);
            tmp.first = 1;
            tmp.second = s[i];
        }
    }
    i64 ans = 0, sum = 0, res = 1;
    for (auto const &x: v) {
        ans += x.first - 1;
        if (x.first > 1) {
            sum += x.first - 1;
            res *= x.first;
            res %= mod;
        }
    }
    cout << ans << ' ' << res * fac[sum] % mod << '\n';
}

signed main() {
    GKD;
    init();
    auto T{1};
    cin >> T;
    while (T--) genshin_start();
    return 0;
}