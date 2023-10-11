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
using i64 = long long;
using ull = unsigned long long;
template<typename T>
using umap = unordered_map<T, T>;
template<class T>
using uset = unordered_set<T, T>;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;

template<typename T>
inline constexpr T qpow(T a, T n, T mod) {
    T ans = 1;
    while (n) {
        if (n & 1) ans *= a;
        n >>= 1;
        a *= a;
        if (mod > 0) {
            ans %= mod;
            a %= mod;
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

int a[200005];

void init() {
    a[1] = 3;
    for (int i = 2; i <= 200000; i++) {
        a[i] = a[i - 1] + 2;
    }
}

auto genshin_start() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
    }
}

signed main() {
    GKD;
    init();
    auto T{1};
    cin >> T;
    while (T--) genshin_start();
    return 0;
}