#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;

template<typename T>
inline T qpow(T const &a, T n, T const &mod) {
    if (n == 0)
        return 1;
    else if (n % 2 == 1)
        return ((qpow(a, n - 1, mod) % mod) * (a % mod)) % mod;
    else {
        T temp = qpow(a, n / 2, mod) % mod;
        return (temp * temp) % mod;
    }
}

template<typename T>
bool isPrime(T num) {
    if (num == 1 || num == 4)
        return false;
    if (num == 2 || num == 3)
        return true;
    if (num % 6 != 1 && num % 6 != 5)
        return false;
    T tmp = sqrt(num);
    for (T i = 5; i <= tmp; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

const int N = 1e7 + 100;
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

const ll mod = 1e9 + 7;

auto genshin_start() {
    ll n, m;
    cin >> n >> m;
    ll ans = 0;
    ll choose = 1;
    for (ll i = 0; i <= m; i++) {
        if (i > 0) {
            choose = (choose * (m - i + 1)) % mod;
            choose = (choose * qpow(i, mod - 2, mod)) % mod;
        }
        ans = (ans + ((i & 1ll) == 0 ? 1 : -1) * (choose % mod) * (qpow(qpow(2ll, m - i, mod) - 1ll, n, mod) % mod)) %
              mod;
        if (ans < 0)ans += mod;
    }
    cout << ans << '\n';
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) genshin_start();
    return 0;
}