#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;

template<typename T>
constexpr T qpow(T a, T n) {
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
constexpr bool isPrime(T num) {
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

constexpr void get_primes(int n) {
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

struct node {
    int l, r;

    bool operator<(const node &b) const {
        if (l == b.l) {
            return r < b.r;
        }
        return l < b.l;
    }
} a[200005];

auto solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r;
    }
    int fl = a[1].l, fr = a[1].r;
    bool flag = false;
    for (int i = 2; i <= m + 1; i++) {
        if (fr < a[i].l || fl > a[i].r) {
            flag = true;
            break;
        }
        fl = max(fl, a[i].l);
        fr = min(fr, a[i].r);
    }
    if (m == n - 1) {
        cout << (flag ? 0 : fr - fl + 1) << '\n';
        return;
    }
    ll ans = 0;
    if (!flag) {
        a[n + 1].l = fl, a[n + 1].r = fr;
        n++;
        sort(a + m + 2, a + n + 1);
    } else {
        sort(a + m + 2, a + n + 1);
    }
    fl = a[m + 2].l, fr = a[m + 2].r;
    for (int i = m + 2; i <= n; i++) {
        if (a[i].l > fr) {
            ans += fr - fl + 1;
            fl = a[i].l;
            fr = a[i].r;
        } else {
            fr = max(fr, a[i].r);
            fl = min(fl, a[i].l);
        }
    }
    ans += fr - fl + 1;
    cout << ans << '\n';
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}