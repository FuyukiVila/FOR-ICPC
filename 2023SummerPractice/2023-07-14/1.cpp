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
constexpr T qpow(T a, T n, T mod) {
    if (n == 0)
        return 1;
    else if (n % 2 == 1)
        return ((qpow(a, n - 1, mod) % mod) * (a % mod)) % mod;
    else {
        T temp = qpow(a, n / 2, mod) % mod;
        return (temp * temp) % mod;
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

//玩原神导致的
int n, m;
constexpr int MAXN = 1.4e5 + 5;
constexpr ll mod = 998244353;
int a[MAXN];
//int b[MAXN];
//
//struct tree {
//    int l, r;
//    int value;
//
//    constexpr auto operator+(tree &b) {
//        auto tree = *this;
//        tree.value += b.value;
//        return tree;
//    }
//} t[MAXN * 4];
//
//void build(int l = 1, int r = n, int p = 1) {
//    t[p].l = l, t[p].r = r;
//    if (l == r) {
//        t[p].value = 1;
//        return;
//    }
//    int mid = (l + r) >> 1;
//    build(l, mid, p * 2), build(mid + 1, r, p * 2 + 1);
//    t[p] = t[p * 2] + t[p * 2 + 1];
//
//    int pos1 = l, pos2 = mid + 1;//n
//    int pos = l;
//    while (pos2 <= r && pos1 <= mid) {
//        while (pos1 <= mid && a[pos1] <= a[pos2]) {
//            pos1++;
//            b[pos++] = a[pos1];
//        }
//        if (pos1 > mid)break;
//        t[p].value += mid - pos1 + 1;
//        b[pos++] = a[pos2++];
//    }
//
//}

void genshin_start() {
//    cin >> n >> m;
//    for (int i = 1; i <= n; i++) {
//        cin >> a[i];
//    }
    cout << 1 * qpow(4ll, mod - 2, mod);
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}