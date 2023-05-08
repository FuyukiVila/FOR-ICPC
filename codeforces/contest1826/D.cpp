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

ll a[100005];

auto solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)cin >> a[i];
    pair<ll, int> max1(0, 0), max2(0, 0), max3(0, 0);
    int l = 1, r = 3;
    for (int i = 1; i <= 3; i++) {
        if (a[i] >= max1.first) {
            max3 = max2;
            max2 = max1;
            max1 = {a[i], i};
        } else if (a[i] >= max2.first) {
            max3 = max2;
            max2 = {a[i], i};
        } else if (a[i] >= max3.first) {
            max3 = {a[i], i};
        }
    }
    for (int i = 4; i <= n; i++) {
        if (a[i] >= max3.first) {
            auto tmp1 = max1, tmp2 = max2, tmp3 = max3;
            if (a[i] >= tmp1.first) {
                tmp3 = tmp2;
                tmp2 = tmp1;
                tmp1 = {a[i], i};
            } else if (a[i] >= tmp2.first) {
                tmp3 = tmp2;
                tmp2 = {a[i], i};
            } else if (a[i] >= tmp3.first) {
                tmp3 = {a[i], i};
            }
            int l1 = min(tmp1.second, min(tmp2.second, tmp3.second));
            if (tmp1.first + tmp2.first + tmp3.first - (i - l1) > max1.first + max2.first + max3.first - (r - l)) {
                max1 = tmp1;
                max2 = tmp2;
                max3 = tmp3;
                l = l1;
                r = i;
            }
        }
    }
    cout<<l<<' '<<r<<'\n';
    set<pair<ll, int>, greater<> > s;
    for (int i = l; i <= r; i++) {
        s.insert({a[i], i});
    }
    ll ans = max1.first + max2.first + max3.first - (r - l);
    for (int i = l + 1; i <= r - 2; i++) {
        ll tmp = 0;
        auto pos = s.begin();
        for (int j = 1; j <= 3; j++) {
            for (auto k = pos; k != s.end(); k++) {
                if (k->second < i)continue;
                else {
                    tmp += k->first;
                    pos = ++k;
                    break;
                }
            }
        }
        ans = max(ans, tmp - (r - i));
    }
    for (int i = r - 1; i >= l + 2; i--) {
        ll tmp = 0;
        auto pos = s.begin();
        for (int j = 1; j <= 3; j++) {
            for (auto k = pos; k != s.end(); k++) {
                if (k->second > i)continue;
                else {
                    tmp += k->first;
                    pos = ++k;
                    break;
                }
            }
        }
        ans = max(ans, tmp - (i - l));
    }
    cout << ans << '\n';
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}