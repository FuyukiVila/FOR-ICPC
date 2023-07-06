#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;

template<typename T>
inline T qpow(T a, T n) {
    if (n == 0)
        return 1;
    else if (n % 2 == 1)
        return (qpow(a, n - 1) * a);
    else {
        T temp = qpow(a, n / 2);
        return temp * temp;
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

ll choose(ll x, ll n) {
    ll res = 1;
    if (n > x) return 0;
    for (ll i = x; i > x - n; i--) {
        res *= i;
    }
    for (ll i = 1; i <= n; i++) {
        res /= i;
    }
    return res;
}

int a[100005];

auto solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    int low[4] = {0,0,0,0};
    int pos = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] != a[i - 1])pos++;
        if (pos > 3)break;
        low[pos]++;
    }
    if (low[1] >= 3) {
        cout << choose(low[1], 3);
    } else if (low[1] + low[2] >= 3) {
        if (low[1] == 1) {
            cout << choose(low[2], 2);
        } else {
            cout << low[2];
        }
    } else {
        cout << low[1] * low[2] * low[3];
    }
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) solve();
    return 0;
}