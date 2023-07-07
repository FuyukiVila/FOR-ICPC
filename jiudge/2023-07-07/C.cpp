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

ll c[300005];
ll _c[300005];

auto solve() {
    ll n, k;
    ll sum = 0;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        _c[i] = c[i];
        sum += c[i];
    }
    c[0] = 0;
    c[n + 1] = 0;
    ll ans = 0;
    ll l = 1, r = sum / k;
    while (l <= r) {
        for (int i = 1; i <= n; i++) {
            c[i] = _c[i];
        }
        ll mid = (l + r) / 2;
        ll cnt = 0;
        for (int i = 1; i <= n; i++) {
            ll tmp = c[i - 1] + c[i];
            cnt += tmp / mid;
            tmp = tmp / mid * mid;
            tmp -= c[i - 1];
            if (tmp > 0) {
                if (c[i] >= tmp) {
                    c[i] -= tmp;
                } else {
                    tmp -= c[i];
                    c[i] = 0;
                    c[i + 1] -= tmp;
                }
            }
        }
        if (cnt >= k) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
//    cout << l << ' ' << r << '\n';
    cout << r * k << '\n';
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}