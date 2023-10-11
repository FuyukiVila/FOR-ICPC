#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

#define dbg(x...)                                                              \
    do {                                                                       \
        std::cout << #x << " -> ";                                             \
        err(x);                                                                \
    } while (0)

void err() { std::cout << std::endl; }

template<class T, class... Ts>
void err(T arg, Ts &...args) {
    std::cout << arg << ' ';
    err(args...);
}

using namespace std;
using ll = long long;
using ull = unsigned long long;
template<typename T> using umap = unordered_map<T, T>;
template<class T> using uset = unordered_set<T, T>;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
const int mod = 0;

template<typename T>
inline constexpr T qpow(T _a, T _n, T _mod = mod) {
    T ans = 1;
    while (_n) {
        if (_n & 1)
            ans *= _a;
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
        if (!st[i])
            minp[i] = i, primes.emplace_back(i);
        for (int j = 0; primes[j] * i <= n; j++) {
            int t = primes[j] * i;
            st[t] = true;
            minp[t] = primes[j];
            if (i % primes[j] == 0)
                break;
        }
    }
}

std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_int_distribution<ll> ranint(1, 1e18);

// 玩原神导致的

struct node {
    int note{};
    ll score{};

    bool operator<(const node &a) const { return score > a.score; }
} a[200005];

void genshin_start() {
    int n, k, m, x;
    int sum = 0;
    cin >> n >> k >> m >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].note;
        a[i].score = 0;
        for (int j = 1; j <= a[i].note; j++) {
            sum++;
            a[i].score += (sum + (k - 1)) / k;
        }
        a[i].score += a[i - 1].score;
    }
    ll ans = a[n].score;
    for (int i = 1; i <= n; i++) {
        a[i].score = a[min(i + x, n)].score - a[i].score;
    }
    sort(a + 1, a + n + 1);
    ans += a[1].score * m;
    cout << ans << '\n';
}
//重复变化
signed main() {
    GKD;
    auto T = 1;
    // cin >> T;
    while (T--)
        genshin_start();
    return 0;
}