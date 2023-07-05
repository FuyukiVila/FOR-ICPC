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

auto solve() {
    double h, c, t;
    cin >> h >> c >> t;
    double two = (h + c) / 2;
    int ans = 2;
    double minn = abs(two - t);
    if (two >= t) {
        cout << 2 << '\n';
    } else {
        int l = 1;
        int r = 1000000;
        while (l <= r) {
            int mid = (l + r) / 2;
            double tmp = ((double(mid) + 1.0) * h + double(mid) * c) / (2.0 * double(mid) + 1.0);
            if (tmp > t) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        for (int mid = max(0, l - 100); mid <= l + 100; mid++) {
            double tmp = abs(t - ((double(mid) + 1.0) * h + double(mid) * c) / (2.0 * double(mid) + 1.0));
            if (tmp < minn) {
                ans = mid * 2 + 1;
                minn = tmp;
            }
        }
        cout << ans << '\n';
    }
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}