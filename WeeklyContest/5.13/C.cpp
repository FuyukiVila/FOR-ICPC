
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
    int n;
    cin >> n;
    vector<ll> a(n + 1, 0);
    for (int i = 1; i <= n; i++)cin >> a[i];
    if (n % 3 != 0) {
        cout << "No\n";
        return;
    }
    sort(a.begin(), a.end());
    ll ans[3] = {0, 0, 0};
    for (int i = 1; i <= n / 3; i++) {
        ans[0] += a[i];
    }
    for (int i = n / 3 + 1; i <= n / 3 * 2; i++) {
        ans[1] += a[i];
    }
    for (int i = n / 3 * 2 + 1; i <= n; i++) {
        ans[2] += a[i];
    }
    if (ans[0] == ans[2]) {
        cout << "No\n";
        return;
    }
    if (ans[0] == ans[1]) {
        ll k = a[1];
        for (int i = n / 3 * 2 + 1; i <= n; i++) {
            ll tmp[3] = {(ans[0] - k + a[i]), (ans[1]),
                         (ans[2] - a[i] + k)};
            if (tmp[0] != tmp[1] && tmp[1] != tmp[2] && tmp[0] != tmp[2]) {
                cout << "Yes\n";
                swap(a[i], a[1]);
                for (int j = 1; j <= n / 3; j++) {
                    cout << a[j] << ' ';
                }
                cout << '\n';
                for (int j = n / 3 + 1; j <= n / 3 * 2; j++) {
                    cout << a[j] << ' ';
                }
                cout << '\n';
                for (int j = n / 3 * 2 + 1; j <= n; j++) {
                    cout << a[j] << ' ';
                }
                cout << '\n';
                return;
            }
        }
    } else if (ans[1] == ans[2]) {
        ll k = a[n];
        for (int i = 1; i <= n / 3; i++) {
            ll tmp[3] = {(ans[0] + k - a[i]), (ans[1]),
                         (ans[2] + a[i] - k)};
            if (tmp[0] != tmp[1] && tmp[1] != tmp[2] && tmp[0] != tmp[2] && tmp[0] > 0) {
                cout << "Yes\n";
                swap(a[i], a[n]);
                for (int j = 1; j <= n / 3; j++) {
                    cout << a[j] << ' ';
                }
                cout << '\n';
                for (int j = n / 3 + 1; j <= n / 3 * 2; j++) {
                    cout << a[j] << ' ';
                }
                cout << '\n';
                for (int j = n / 3 * 2 + 1; j <= n; j++) {
                    cout << a[j] << ' ';
                }
                cout << '\n';
                return;
            }
        }
    } else if (ans[0] != ans[1] && ans[1] != ans[2]) {
        cout << "Yes\n";
        for (int j = 1; j <= n / 3; j++) {
            cout << a[j] << ' ';
        }
        cout << '\n';
        for (int j = n / 3 + 1; j <= n / 3 * 2; j++) {
            cout << a[j] << ' ';
        }
        cout << '\n';
        for (int j = n / 3 * 2 + 1; j <= n; j++) {
            cout << a[j] << ' ';
        }
        cout << '\n';
        return;
    }
    cout << "No\n";
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) solve();
    return 0;
}