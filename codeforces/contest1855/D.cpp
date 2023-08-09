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
template<typename T>
using umap = unordered_map<T, T>;
template<typename T>
using uset = unordered_set<T, T>;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
const int mod = 0;

template<typename T>
inline constexpr T qpow(T _a, T _n, T _mod = mod) {
    T ans = 1;
    while (_n) {
        if (_n & 1) ans *= _a;
        _n >>= 1;
        _a *= _a;
        if (_mod > 0) {
            ans %= _mod;
            _a %= _mod;
        }
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

vector<pair<int, int>> ans1, ans2;
int maxnf, maxnz, maxnfpos, maxnzpos;
int n;
int a[30];

void zs() {
    while (abs(maxnz) < abs(maxnf)) {
        ans1.emplace_back(maxnzpos, maxnzpos);
        maxnz *= 2;
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] < 0) {
            ans1.emplace_back(i, maxnzpos);
        }
    }
    for (int i = 2; i <= n; i++) {
        ans1.emplace_back(i, i - 1);
    }
}

void fs() {
    while (abs(maxnf) < abs(maxnz)) {
        ans2.emplace_back(maxnfpos, maxnfpos);
        maxnf *= 2;
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] > 0) {
            ans2.emplace_back(i, maxnfpos);
        }
    }
    for (int i = n - 1; i >= 1; i--) {
        ans2.emplace_back(i, i + 1);
    }
}

void solve() {
    cin >> n;
    maxnz = 0;
    maxnf = 0;
    ans1.clear();
    ans2.clear();
    bool flag = true;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i >= 1 && a[i] < a[i - 1]) {
            flag = false;
        }
        if (a[i] > maxnz && a[i] > 0) {
            maxnz = a[i];
            maxnzpos = i;
        }
        if (a[i] < maxnf && a[i] < 0) {
            maxnf = a[i];
            maxnfpos = i;
        }
    }
    if (flag) {
        cout << 0 << '\n';
        return;
    }
    if (!maxnf) {
        cout << n - 1 << '\n';
        for (int i = 2; i <= n; i++) {
            cout << i << ' ' << i - 1 << '\n';
        }
        return;
    }
    if (!maxnz) {
        cout << n - 1 << '\n';
        for (int i = n - 1; i >= 1; i--) {
            cout << i << ' ' << i + 1 << '\n';
        }
        return;
    }
    auto _maxnz = maxnz;
    zs();
    maxnz = _maxnz;
    fs();
    if (ans1.size() > ans2.size()) {
        swap(ans1, ans2);
    }
    cout << ans1.size() << '\n';
    for (auto const &[x, y]: ans1) {
        cout << x << ' ' << y << '\n';
    }
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}