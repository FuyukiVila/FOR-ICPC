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


pair<ll, ll> init(int n) {
    ll a[305]{};
    ll res = 0;
    ll sum = 1;
    for (ll i = 1; i <= 2 * n; i++) {
        sum *= i;
        a[i] = i;
    }
    for (ll i = 1; i <= sum; i++) {
        for (ll j = 1; j <= 2 * n; j++) {
            if (j == n * 2 - 1) {
                res += n * 2;
                break;
            }
            if (a[j] <= n && a[j + 1] < a[j] || a[j] > n && a[j + 1] > a[j]) {
                res += j + 1;
                break;
            }
        }
        next_permutation(a + 1, a + 2 * n + 1);
    }
    return {res, sum};
}

auto genshin_start() {
    for (int i = 1; i <= 6; i++) {
        auto x = init(i);
        cout << x.first << ' ' << x.second << '\n';
//        cout << x.first / x.second << ' ' << x.first % x.second << '\n';
    }

}

signed main() {
//    GKD;
    auto T{1};
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}