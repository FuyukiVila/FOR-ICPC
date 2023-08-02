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
template<typename T>
using uset = unordered_set<T, T>;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
const int mod = 0;

template<typename T>
inline constexpr T qpow(T _a, T _n, T _mod = mod) {
    T ans = 1;
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

void ThrowException() {
    cout << -1;
    exit(0);
}

class Program {
private:
    unordered_map<string, vector<int>> v{};
public:
    void check(const string &name, int pos) {
        if (pos >= v[name].size()) {
            ThrowException();
        }
    }

    void initArray(const string &name, int size) {
        v[name].resize(size, 0);
    }

    void changeArray(const string &name, int pos, int value) {
        check(name, pos);
        v[name][pos] = value;
    }

    int getVal(const string &name, int pos) {
        check(name, pos);
        return v[name][pos];
    }

    pair<string, int> decode(const string &s) {
        pair<string, int> res{};
        string ss;
        for (int i = 0; i <= s.size(); i++) {
            if (s[i] == '[') {
                ss = s.substr(i + 1);
                break;
            }
            res.first.push_back(s[i]);
        }
        ss.pop_back();
        try {
            res.second = stoi(ss);
        }
        catch (...) {
            auto r = decode(ss);
            res.second = getVal(r.first, r.second);
        }
        return res;
    }
};
Program p;
//玩原神导致的
void genshin_start() {
    string s;
    while (getline(cin, s)) {
        string tmp;
        for (int i = 0; i < s.size(); i++) {
            char x = s[i];
            if (x == ' ') {
                if (tmp == "int") {
                    string ss = s.substr(i + 1);
                    auto res = p.decode(ss);
                    p.initArray(res.first, res.second);
                } else if (tmp == "cout") {
                    string ss = s.substr(i + 1);
                    auto res = p.decode(ss);
                    cout << p.getVal(res.first, res.second) << '\n';
                } else {
                    string ss = s.substr(i + 1);
                    int value = 0;
                    try {
                        value = stoi(ss);
                    }
                    catch (...) {
                        value = p.decode(ss).second;
                    }
                    auto res = p.decode(tmp);
                    p.changeArray(res.first, res.second, value);
                }
                break;
            }
            tmp.push_back(x);
        }
    }
}

signed main() {
//    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}