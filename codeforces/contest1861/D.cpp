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

auto genshin_start() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<array<int, 3> > k;
    array<int, 3> tmp{0, 0, 0};
    for (int i = 1; i <= n; i++) {
        if (tmp[0] == 0) {
            tmp[0] = tmp[1] = i;
        } else if (a[i] == a[i - 1] || tmp[2] == 1 && a[i] < a[i - 1] || tmp[2] == -1 && a[i] > a[i - 1]) {
            k.emplace_back(tmp);
            tmp = {0, 0, 0};
            i--;
        } else if (tmp[2] == 0) {
            tmp[1] = i;
            if (a[i] > a[i - 1])tmp[2] = 1;
            else tmp[2] = -1;
        } else {
            tmp[1] = i;
        }
    }
    if (tmp[0] != 0)k.emplace_back(tmp);
    if (k.size() == 1) {
        if (k[0][2] == -1) {
            cout << "1\n";
        } else {
            cout << "0\n";
        }
        return;
    }
    int MIN = -INF;
    int ans = 0;
    for (int i = 0; i < k.size(); i++) {
        auto x = k[i];
        int minn = a[x[0]], maxn = a[x[1]];
        if (x[2] == -1) {
            if (i == 0 || k[i - 1][2] != -1)ans++;
            minn = -minn;
            maxn = -maxn;
        }
        if (minn <= MIN) ans++;
        MIN = maxn;
    }
    cout << ans << '\n';
}

signed main() {
    GKD;
    auto T{1};
    cin >> T;
    while (T--) genshin_start();
    return 0;
}