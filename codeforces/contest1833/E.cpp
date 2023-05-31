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

int g[200005];
int a[200005];

int find(int x) {
    if (g[x] == x)return x;
    return g[x] = find(g[x]);
}

bool is[200005];

auto solve() {
    clr(is, false);
    int n;
    cin >> n;
    map<int, vector<int> > m;
    for (int i = 1; i <= n; i++)g[i] = i;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        g[find(i)] = find(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        m[find(i)].emplace_back(i);
    }
    for (int i = 1; i <= n; i++) {
        if (i != a[a[i]]) {
            is[a[i]] = true;
        }
    }
    int cnt = m.size();
    int q = 0;
    for (auto const &[i, j]: m) {
        bool flag = true;
        for (auto x: j) {
            if (!is[x]) {
                flag = false;
                break;
            }
        }
        if (!flag)q++;
    }
    cout << cnt - max(q, 1) + 1 << ' ' << cnt << '\n';
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}