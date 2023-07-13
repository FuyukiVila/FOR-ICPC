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

constexpr int N = 1e8 + 5;
int minp[N];
int num[N];
vector<int> primes;
bool st[N];

void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        num[i] = num[i - 1];
        if (!st[i]) num[i]++, minp[i] = i, primes.emplace_back(i);
        for (int j = 0; primes[j] * i <= n; j++) {
            int t = primes[j] * i;
            st[t] = true;
            minp[t] = primes[j];
            if (i % primes[j] == 0) break;
        }
    }
}

//玩原神导致的
const int MAXN = qpow(2, 15) + 5;
bool is[MAXN];
int pows[22];

void init() {
    pows[0] = 1;
    for (int i = 1; i <= 15; i++) {
        pows[i] = pows[i - 1] * 2;
    }
    for (int i = 1; i <= qpow(2, 15); i++) {
        num[i] = num[i - 1];
        if (!is[i]) {
            num[i]++;
            for (int j = 1; j <= 15; j++) {
                if (pows[j] > i) {
                    is[pows[j] - i] = true;
                }
            }
        }
    }
    cout<<num[990];
}

void genshin_start() {
    int n;
    cin >> n;
    if (n <= qpow(2, 15))cout << num[n] << '\n';
    else cout << num[n] + n - qpow(2, 15) << '\n';
}

signed main() {
    init();
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) genshin_start();
    return 0;
}