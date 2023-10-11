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

auto genshin_start() {
    ll n;
    cin >> n;
    get_primes(1000000);
    map<ll, ll> cnt;
    ll m = n;
    while (m > 1) {
        cnt[minp[m]]++;
        m /= minp[m];
    }
    int q;
    cin >> q;
    m = n;
    auto ccnt = cnt;
    while (q--) {
        int op;
        cin >> op;
        if (op == 2) {
            ccnt = cnt;
            m = n;
        } else {
            ll x;
            cin >> x;

            while (x > 1) {
                ccnt[minp[x]]++;
                x /= minp[x];
            }
            m *= x;
            bool flag = true;
            map<int, int> cnt2;
            for (auto &[i, c]: ccnt) {
                int tmp = c + 1;
                while (tmp > 1) {
                    cnt2[minp[tmp]]++;
                    tmp /= minp[tmp];
                }
            }
            for (auto const &[i, j]: cnt2) {
                if (j > ccnt[i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}

signed main() {
    GKD;
    auto T{1};
    cin >> T;
    while (T--) genshin_start();
    return 0;
}