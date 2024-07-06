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

#define int ll
int ans[2004][504];

void idol_produce(int testCase) {
    /*Code Here*/
    int k, t;
    cin >> k >> t;
//    filebuf fb;
//    fb.open("out.txt", ios::out);
//    ostream out(&fb);
    int j = 1;
    for (int i = 1; i <= 1000; i++) {
        for (int p = 1; p <= 500; p++) {
            ans[i][p] = j;
            j++;
        }
    }
    for (int i = 1001; i <= 1500; i++) {
        j = i - 1000;
        for (int p = 1; p <= 500; p++) {
            ans[i][p] = j;
            j += 500;
        }
//        cout << ans[i][500] << '\n';
    }
    for (int i = 1501; i <= 2000; i++) {
        j = 250000 + i - 1500;
        for (int p = 1; p <= 500; p++) {
            ans[i][p] = j;
            j += 500;
//            if (j == 500000) {
//                cout << "YES\n";
//            }
        }
//        cout << ans[i][500] << '\n';
    }
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= t; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }

}

signed main() {
    GKD;
    init();
    int T = 1;
//    cin >> T;
    for (int i = 1; i <= T; i++) {
        idol_produce(i);
    }
    return 0;
}
