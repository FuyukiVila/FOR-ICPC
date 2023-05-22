#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
const ll mod = 998244353;

template<typename T>
inline T qpow(T a, T n) {
    if (n == 0)
        return 1;
    else if (n % 2 == 1)
        return (qpow(a, n - 1) * a) % mod;
    else {
        T temp = qpow(a, n / 2) % mod;
        return temp * temp % mod;
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

ll choose(ll n, ll k) {
    if (n < 0)return 0;
    if (k > n || k < 0)return 0;
    ll ans = 1;
    ll q = 1;
    for (ll i = n; i > n - k; i--) {
        ans = ans * i % mod;
    }
    for (ll i = 1; i <= k; i++) {
        q *= i;
    }
    return (ans * qpow(q, mod - 2) % mod) % mod;
}

map<ll, ll> m;

auto solve() {
    ll n;
    cin >> n;
    ll q = choose(n, 3);
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        m[x] += 1;
    }
    ll p = 0;
    p = (p + (choose(m[0], 1) % mod) * (choose(n - m[0] - m[1], 2) % mod)) % mod;
//    cout << p << '\n';
    p = (p + (choose(m[0], 2) % mod) * (choose(n - m[0] - m[1], 1) % mod)) % mod;
//    cout << p << '\n';
    p = (p + (choose(m[0], 3) % mod) * (choose(n - m[0] - m[1], 0) % mod)) % mod;
//    cout << p << '\n';
    p = (p + choose(m[0], 1) % mod * choose(m[1], 1) % mod * choose(n - m[0] - m[1] - m[2], 1) % mod * 2) % mod;
//    cout << p << '\n';
    p = (p + choose(m[0], 2) % mod * choose(m[1], 1) % mod * choose(n - m[0] - m[1] - m[2], 0) % mod * 2) % mod;
//    cout << p << '\n';
    p = (p + choose(m[0], 1) % mod * choose(m[1], 2) % mod * choose(n - m[0] - m[1] - m[2], 0) % mod * 2) % mod;
//    cout << p << '\n';
    p = (p + choose(m[0], 1) % mod * choose(m[1], 1) % mod * choose(m[2], 1) % mod * 3) % mod;
//    cout << p << ' ' << q << '\n';
    cout << (p * qpow(q, mod - 2) % mod) % mod << "\n";
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) solve();
    return 0;
}