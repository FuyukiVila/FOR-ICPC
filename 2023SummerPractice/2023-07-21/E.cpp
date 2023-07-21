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


auto genshin_start() {
    ll x;
    ll y;
    cin >> x;
    ll _x = x;
    if (x == 0) {
        cout << 0 << '\n';
        return;
    }
    while (true) {
        if (x > 1e18 || x < 0)break;
        y = ceil(sqrt(x));
        if (y > 1e9 + 10 || y < 0)break;
        for (int i = -2; i <= 2; i++) {
            ll _y = y + i;
            if (_y < 0 || _y > 1e9)continue;
            ll tmp1 = (_y) * (_y);
            ll d = 1;
            for (int k = 0; k <= 18; i++) {
                ull tmp2 = tmp1 / d;
                if (tmp2 < x) {
                    break;
                } else if (tmp2 == x) {
                    cout << tmp1 << '\n';
                    return;
                }
                d *= 10;
            }
        }
        x *= 10;
    }
    cout << -1 << '\n';
}

signed main() {
    GKD;
    auto T{1};
    cin >> T;
    while (T--) genshin_start();
    return 0;
}