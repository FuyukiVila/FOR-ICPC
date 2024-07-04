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

constexpr int _N = 1e7 + 100;
vector<int> minp(_N);
vector<int> primes;
bitset<_N> st;

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

struct Manacher {

    // 求奇数回文串
    std::vector<int> static getOddPalindrome(const std::string &s) {
        std::vector<int> d1(s.size());
        for (int i = 0, l = 0, r = -1; i < s.size(); i++) {
            int k = (i > r) ? 1 : std::min(d1[l + r - i], r - i + 1);
            while (0 <= i - k && i + k < s.size() && s[i - k] == s[i + k]) {
                k++;
            }
            d1[i] = k--;
            if (i + k > r) {
                l = i - k;
                r = i + k;
            }
        }
        return d1;
    }

    // 求偶数回文串
    std::vector<int> static getEvenPalindrome(const std::string &s) {
        std::vector<int> d2(s.size());
        for (int i = 0, l = 0, r = -1; i < s.size(); i++) {
            int k = (i > r) ? 0 : std::min(d2[l + r - i + 1], r - i + 1);
            while (0 <= i - k - 1 && i + k < s.size() &&
                   s[i - k - 1] == s[i + k]) {
                k++;
            }
            d2[i] = k--;
            if (i + k > r) {
                l = i - k - 1;
                r = i + k;
            }
        }
        return d2;
    }
};

class KMP {
    std::string pattern;
    std::vector<int> next;

    void buildNext() {
        for (int i = 1, j = 0; i < pattern.size(); i++) {
            while (j && pattern[i] != pattern[j]) j = next[j - 1];
            if (pattern[i] == pattern[j]) j++;
            next[i] = j;
        }
    }

public:
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
        for (size_t i = pos, j = 0; i < txt.size(); i++) {
            while (j && txt[i] != pattern[j]) j = next[j - 1];
            if (txt[i] == pattern[j]) j++;
            if (j == pattern.size()) {
                return i - pattern.size() + 1;
            }
        }
        return -1;
    }

    KMP(std::string pattern) : pattern(pattern) {
        next.resize(pattern.size());
        buildNext();
    }
};

inline void init() {
    /*Init Here*/
}

void idol_produce(int testCase) {
    /*Code Here*/
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    KMP kmp(t);
    vector<size_t> a = kmp.searchAll(s);
    s = "#" + s;
    auto d = Manacher::getOddPalindrome(s);
    vector<unsigned int> pre(n + 1);
    vector<unsigned int> sum(n + 1);
    for (auto const &x: a) {
        pre[x + 1]++;
    }
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + pre[i] * i;
        pre[i] = pre[i - 1] + pre[i];
    }
    unsigned int ans = 0;
    for (int i = 1; i <= n; i++) {
        int l = i - d[i] + 1, r = i + d[i] - m;
        if (l > r) continue;
        int mid = (l + r) >> 1;
        ans += (sum[mid] - sum[l - 1]) - (pre[mid] - pre[l - 1]) * (l - 1);
        if (mid != r) ans += (pre[r] - pre[mid]) * (r + 1) - (sum[r] - sum[mid]);
    }
    cout << ans;
}

signed main() {
    GKD;
    init();
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        idol_produce(i);
    }
    return 0;
}
