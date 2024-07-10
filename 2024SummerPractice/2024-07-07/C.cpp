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
//#define LOCAL
//#define PRIME

#include <bits/stdc++.h>

#ifdef LOCAL

#define dbg(x...)                                                              \
    do {                                                                       \
        std::cout << #x << " -> ";                                             \
        err(x);                                                                \
    } while (0);
#else
#define dbg(x...) 114514;
#endif

void err() { std::cout << std::endl; }

template<class T, class... Ts>
void err(T arg, Ts &...args) {
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

#ifdef PRIME

const int N = 1e7 + 100;
vector<int> minp(N);
vector<int> primes;
bitset<N> st;

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

#endif

inline void init() {
    /*Init Here*/
}

void idol_produce(int testCase) {
    /*Code Here*/
    int n;
    cin >> n;
    if (n == 2) {
        cout << "-1\n";
        return;
    }
    if (n % 2 == 1) {
        deque<int> q;
        for (int i = 1; i <= n; i++) {
            q.push_back(i);
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < n; j++) {
                cout << q[j] << " \n"[j == n - 1];
            }
            q.push_back(q.front());
            q.pop_front();
        }
        return;
    }
    vector <vector<int>> a(n + 1, vector<int>(n + 1, n));
    deque<int> q;
    for (int i = 1; i <= n - 1; i++) {
        q.push_back(i);
    }
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            a[i][j + 1] = q[j];
        }
        q.push_back(q.front());
        q.pop_front();
    }
    for (int i = 2; i <= n; i++) {
        int tmp = a[i][i - 1];
        a[i][i - 1] = n;
        a[i][n] = tmp;
        a[n][i - 1] = tmp;
    }
    a[n][n] = n - 1;
    for (int i = 1; i < n; i++) {
        if (a[i][i] == n - 1) {
            a[i][i] = n;
            for (int j = 1; j <= n; j++) {
                if (a[j][i] == n && j != i) {
                    a[j][i] = n - 1;
                    for (int k = 1; k <= n; k++) {
                        if (a[j][k] == n - 1 && k != i) {
                            a[j][k] = n;
                            a[k + 1][k] = n - 1;
                            for (int i = 1; i <= n; i++) {
                                for (int j = 1; j <= n; j++) {
                                    cout << a[i][j] << " \n"[j == n];
                                }
                            }
                            return;
                        }
                    }
                }
            }
        }
    }
}

signed main() {
    GKD;
    init();
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        idol_produce(i);
    }
    return 0;
}
