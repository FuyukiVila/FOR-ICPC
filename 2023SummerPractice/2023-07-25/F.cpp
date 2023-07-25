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

char a[200][200];
char b[200][200];
char c[200][200];
char d[200][200];
char e[200][200];

auto genshin_start() {
    int n, z;
    cin >> n >> z;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    int m = (n * z) / 100;
    if (m != (n * z) / 100.0) {
        cout << "error\n";
        return;
    }
    vector<char> s;
    for (int i = 1; i <= n; i++) {
        int pos = 1;
        for (int j = 1; j <= n; j++) {
            if (s.empty() || s.back() == a[i][j]) {
                s.push_back(a[i][j]);
            } else {
                if (s.size() * m % n != 0) {
                    cout << "error\n";
                    return;
                }
                for (int k = pos; k <= pos + s.size() * m / n - 1; k++) {
                    b[i][k] = s.back();
                }
                pos = pos + s.size() * m / n;
                s.clear();
                s.push_back(a[i][j]);
            }
        }
        if (!s.empty()) {
            if (s.size() * m % n != 0) {
                cout << "error\n";
                return;
            }
            for (int k = pos; k <= pos + s.size() * m / n - 1; k++) {
                b[i][k] = s.back();
            }
            pos = pos + s.size() * m / n;
            s.clear();
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            c[j][i] = b[i][j];
        }
    }
//    for (int i = 1; i <= m; i++) {
//        for (int j = 1; j <= n; j++) {
//            cout << c[i][j];
//        }
//        cout << '\n';
//    }
    for (int i = 1; i <= m; i++) {
        int pos = 1;
        for (int j = 1; j <= n; j++) {
            if (s.empty() || s.back() == c[i][j]) {
                s.push_back(c[i][j]);
            } else {
                if (s.size() * m % n != 0) {
                    cout << "error\n";
                    return;
                }
                for (int k = pos; k <= pos + s.size() * m / n - 1; k++) {
                    d[i][k] = s.back();
                }
                pos = pos + s.size() * m / n;
                s.clear();
                s.push_back(c[i][j]);
            }
        }
        if (!s.empty()) {
            if (s.size() * m % n != 0) {
                cout << "error\n";
                return;
            }
            for (int k = pos; k <= pos + s.size() * m / n - 1; k++) {
                d[i][k] = s.back();
            }
            pos = pos + s.size() * m / n;
            s.clear();
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            e[j][i] = d[i][j];
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            cout << e[i][j];
        }
        cout << '\n';
    }
//    for (int i = 1; i <= n; i++) {
//        for (int j = 1; j <= n; j++) {
//            if (s.empty() || s.back() == a[j][i]) {
//                s.push_back(a[j][i]);
//            } else {
//                if (s.size() * m % n != 0) {
//                    cout << "error\n";
//                    return;
//                }
//                s.clear();
//                s.push_back(a[j][i]);
//            }
//        }
//        if (!s.empty()) {
//            if (s.size() * m % n != 0) {
//                cout << "error\n";
//                return;
//            }
//            s.clear();
//        }
//    }
}

signed main() {
    GKD;
    auto T{1};
    cin >> T;
    while (T--) genshin_start();
    return 0;
}