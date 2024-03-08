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

//玩原神导致的
#define int ll

void genshin_start(int testCase) {
    int n;
    cin >> n;
    ll ans = 0;
    vector<ll> b(n + 1);
    vector<int> c(n + 1);
    map<int, map<int, ll> > mod_number; // 各位和的9的模数，对应的末尾数字
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        int tmp = 0;
        ll k = b[i];
        while (k) {
            tmp += k % 10;
            k /= 10;
        }
        mod_number[tmp % 9][b[i] % 10]++;
        c[i] = tmp % 9;
    }
    if (n == 1) {
        cout << 0 << '\n';
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (b[i] >= 10 && b[i] % 4 == 0) {
            if (c[i] == 0) {
                for (auto const &it: mod_number[0]) {
                    ans += it.second;
                }
                ans -= 1;
            } else {
                for (auto const &it: mod_number[9 - c[i]]) {
                    ans += it.second;
                }
            }
        } else if (b[i] < 10) {
            vector<int> w;
            int flag = 0;
            for (int j = 0; j <= 9; j++) {
                if ((j * 10 + b[i]) % 4 == 0) {
                    w.emplace_back(j);
                    if (j == b[i]) {
                        flag = 1;
                    }
                }
            }
            if (c[i] == 0) {
                for (auto const &x: w) {
                    ans += mod_number[0][x];
                }
                ans -= flag;
            } else {
                for (auto const &x: w) {
                    ans += mod_number[9 - c[i]][x];
                }
            }
        }
    }
    cout << ans << '\n';
}

signed main() {
    GKD;
    int T = 1;
//    cin >> T;
    for (int i = 1; i <= T; i++) {
        genshin_start(i);
    }
    return 0;
}

