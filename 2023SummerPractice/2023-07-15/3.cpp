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
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
const ll mod = 1e9 + 7;

template<typename T>
inline constexpr T qpow(T a, T n) {
    T ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        n >>= 1;
        a = (a * a) % mod;
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

//玩原神导致的
int a[1000000];
int q;

void init() {
    a[1] = 2;
    a[2] = 1;
    for (int i = 3;; i++) {
        a[i] = a[i - 1] + a[i - 2];
        if (a[i] > 1e9) {
            q = i - 1;
            break;
        }
    }
}

int l, r;

bool in(int x) {
    if (x >= l && x <= r) {
        return true;
    } else {
        return false;
    }
}

void genshin_start() {
    cin>>l>>r;
    bool flag = false;
    for (int i = 1; i <= 20; i++) {
        int k = qpow(3, i);
        if (in(k))flag = true;
    }
    if (flag || in(1) || in(2) || in(3) || in(4) || in(6) || in(7) || in(14)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

signed main() {
    GKD;
    init();
    auto T = 1;
    cin >> T;
    while (T--) genshin_start();
    return 0;
}