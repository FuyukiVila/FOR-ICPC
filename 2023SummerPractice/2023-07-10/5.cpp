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

bitset<32> a[1000005];
int ans[1000005];

inline int reverse(bitset<32> b, int maxn) {
    for (int i = 0; i <= maxn; i++) {
        b[i] = !b[i];
    }
    return b.to_ulong();
}

void resolve(int s, int t) {
    int r = 0;
    if (s == t)return;
    int maxn = 0;
    for (int i = 31; i >= 0; i--) {
        if (a[t][i] == 1) {
            maxn = i;
            break;
        }
    }
    for (int i = s; i <= t; i++) {
        auto j = reverse(a[i], maxn);
        if (j > t) {
            r = i;
        } else {
            ans[i] = j;
        }
    }
    resolve(s, r);
}

auto genshin_start() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    resolve(0, n - 1);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}