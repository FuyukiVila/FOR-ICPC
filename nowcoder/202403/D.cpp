/*
  ______                 _    _  __      ___ _
 |  ____|               | |  (_) \ \    / (_) |
 | |__ _   _ _   _ _   _| | ___   \ \  / / _| | __ _
 |  __| | | | | | | | | | |/ / |   \ \/ / | | |/ _` |
 | |  | |_| | |_| | |_| |   <| |    \  /  | | | (_| |
 |_|   \__,_|\__, |\__,_|_|\_\_|     \/   |_|_|\__,_|
              __/ |
             |___/
*/

#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))
#define cpy(a, b) memcpy(a, b, sizeof(a))

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
const int INF = 0x3f3f3f3f;
ll mod = 0;

inline ll qpow(ll _a, ll _n, ll _mod = mod) {
    ll ans = 1;
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
vector<int> minp(N);
vector<int> primes;
bitset<N> st;

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

std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_int_distribution<ll> ranint(1, 1e18);

//��ԭ���µ�
void genshin_start(int testCase) {
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll ans = *max_element(a.begin() + 1, a.end());
    if (ans < 0 || n == 1) {
        cout << ans << '\n';
        return;
    }
    if (k == 0) {
        ll tmp = 0;
        for (int i = 1; i <= n; i++) {
            tmp += a[i];
            if (tmp < 0) {
                tmp = 0;
            }
            ans = max(ans, tmp);
        }
        cout << ans << '\n';
    }
    if (k == 1) {
        for (int j = 1; j <= n - 1; j++) {
            swap(a[j], a[j + 1]);
            ll tmp = 0;
            for (int i = 1; i <= n; i++) {
                tmp += a[i];
                if (tmp < 0) {
                    tmp = 0;
                }
                ans = max(ans, tmp);
            }
            swap(a[j], a[j + 1]);
        }
        cout << ans << '\n';
    }
}

signed main() {
    GKD;
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        genshin_start(i);
    }
    return 0;
}

