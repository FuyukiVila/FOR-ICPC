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

bool check(const vector<vector<int>> &ans, int n) {
    vector<vector<int>> a(n * 2 + 1, vector<int>(n * 2 + 1, 0));
    for (auto const &v: ans) {
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v.size(); j++) {
                int p = v[i], q = v[j];
                a[p][q] = 1;
            }
        }
    }
    for (int i = 1; i <= n * 2; i++) {
        for (int j = i + 1; j <= n * 2; j++) {
            if (a[i][j] == 0) {
                cout << i << ' ' << j << '\n';
                return false;
            }
        }
    }
    return true;
}

void print(const vector<vector<int>> &ans) {
//    filebuf fb;
//    fb.open("ans.txt", ios::out);
//    ostream cout(&fb);
    cout << ans.size() << '\n';
    for (auto const &v: ans) {
        for (auto const &x: v) {
            cout << x << ' ';
        }
        cout << '\n';
    }
}

void idol_produce(int testCase) {
    /*Code Here*/
    int n = testCase;
    cin >> n;
    vector<vector<int>> ans;
    if (n == 3) {
        cout << "6\n";
        cout << "1 2 4\n1 2 6\n1 3 5\n2 3 5\n3 4 6\n4 5 6";
        return;
    }
    if (n % 2 == 0) {
        vector<int> tmp1, tmp2;
        for (int i = 1; i <= n; i++) {
            tmp1.emplace_back(i);
            tmp2.emplace_back(i + n);
        }
        ans.emplace_back(tmp1);
        ans.emplace_back(tmp2);
        tmp1.clear(), tmp2.clear();
        for (int i = 1; i <= n / 2; i++) {
            tmp1.emplace_back(i);
            tmp1.emplace_back(i + n);
            tmp2.emplace_back(i + n / 2);
            tmp2.emplace_back(i + n + n / 2);
        }
        ans.emplace_back(tmp1);
        ans.emplace_back(tmp2);
        tmp1.clear();
        tmp2.clear();
        for (int i = 1; i <= n / 2; i++) {
            tmp1.emplace_back(i);
            tmp2.emplace_back(i + n / 2);
            tmp1.emplace_back(i + n / 2 + n);
            tmp2.emplace_back(i + n);
        }
        ans.emplace_back(tmp1);
        ans.emplace_back(tmp2);
        print(ans);
    } else {
        vector<set<int> > a;
        a.push_back({1, 2, 3});
        a.push_back({1, 4, 5});
        a.push_back({1, 3, 6});
        a.push_back({2, 4, 6});
        a.push_back({2, 5, 6});
        a.push_back({3, 4, 5});
        int minn = 7;
        n -= 3;
        for (int i = minn, p = 1; p <= n / 2; i++, p++) {
            a[0].insert(i);
            a[1].insert(i);
            a[3].insert(i);
        }
        for (int i = minn + n / 2, p = 1; p <= n / 2; i++, p++) {
            a[0].insert(i);
            a[2].insert(i);
            a[5].insert(i);
        }
        for (int i = minn + n, p = 1; p <= n / 2; i++, p++) {
            a[1].insert(i);
            a[4].insert(i);
            a[5].insert(i);
        }
        for (int i = minn + n + n / 2, p = 1; p <= n / 2; i++, p++) {
            a[2].insert(i);
            a[3].insert(i);
            a[4].insert(i);
        }
        cout << 6 << '\n';
        for (auto const &s: a) {
            for (auto const &i: s) {
                cout << i << " ";
            }
            cout << '\n';
        }
    }
}
//1 2 3 9 10
//4 5 6 7 8
//1 5 6
//3 7   8
//1 7 2 8
//3 5 2 6

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
