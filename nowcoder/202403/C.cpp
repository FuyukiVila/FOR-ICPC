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
class KMP {
public:
    std::string pattern;
    vector<int> next;

    void buildNext() {
        for (int i = 1, j = 0; i < pattern.size(); i++) {
            while (j && pattern[i] != pattern[j]) j = next[j - 1];
            if (pattern[i] == pattern[j]) j++;
            next[i] = j;
        }
    }

    auto searchAll(std::string txt) {
        std::vector<size_t> p;
        for (size_t i = 0, j = 0; i < txt.size(); i++) {
            while (j && txt[i] != pattern[j]) j = next[j - 1];
            if (txt[i] == pattern[j]) j++;
            if (j == pattern.size()) {
                p.emplace_back(i - pattern.size() + 1);
                j = next[j - 1];
            }
        }
        return p;
    }

    size_t search(std::string txt, size_t pos = 0) {
        int j = 0;
        for (size_t i = pos; i < txt.size(); i++) {
            while (j && txt[i] != pattern[j]) j = next[j - 1];
            if (txt[i] == pattern[j]) j++;
//            if (j == pattern.size()) {
//                j = next[j - 1];
//            }
        }
        return j;
    }

    KMP(std::string pattern) : pattern(pattern) {
        next.resize(pattern.size());
        buildNext();
    }
};

bool check(string s) {
    if (s.size() < 1) {
        return false;
    }
    for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
        if (s[i] != s[j]) {
            return false;
        }
    }
    return true;
}

void genshin_start(int testCase) {
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    int maxn = min(s.size(), t.size());
    KMP kmpt(t), kmps(s);
    int y = kmpt.search(s);
    int x = kmps.search(t);
    int tmp1 = 0, tmp2 = 0;
    for (int i = 0, j = s.size() - 1; i < t.size() && j >= 0; i++, j--) {
        if (t[i] != t[0] || s[j] != t[0]) {
            break;
        }
        tmp2++;
    }
    for (int i = 0, j = t.size() - 1; i < s.size() && j >= 0; i++, j--) {
        if (t[j] != s[0] || s[i] != s[0]) {
            break;
        }
        tmp1++;
    }
    int ans = 0;
    bool flag1 = check(s.substr(0, x));
    bool flag2 = check(t.substr(0, y));
    string strs = s.substr(0, x);
    string strt = t.substr(0, y);
    if (flag1 && flag2) {
        if (x + y <= maxn) {
            ans = max(ans, (x + y) * 2);
        }
    }
    if (flag1 && tmp2) {
        auto kmp = *new KMP(strs);
        int strs_lowerst_circle = strs.size() - kmp.next[strs.size() - 1];
        int k = x;
        while (k + tmp2 >= maxn) {
            k -= strs_lowerst_circle;
        }
        if (k) {
            ans = max(ans, min((k + tmp2) * 2, maxn * 2));
        }
    }
    if (flag2 && tmp1 && y < t.size()) {
        auto kmp = *new KMP(strt);
        int strt_lowerst_circle = strt.size() - kmp.next[strt.size() - 1];
        int k = y;
        while (k + tmp2 >= maxn) {
            k -= strt_lowerst_circle;
        }
        if (k) {
            ans = max(ans, min((k + tmp2) * 2, maxn * 2));
        }
    }
    if (tmp1 && tmp2) {
        ans = max(ans, min((tmp1 + tmp2) * 2, maxn * 2));
    }
    if (ans == 0) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }
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

