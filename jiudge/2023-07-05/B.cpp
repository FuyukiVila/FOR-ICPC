#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;

template<typename T>
inline T qpow(T a, T n) {
    if (n == 0)
        return 1;
    else if (n % 2 == 1)
        return (qpow(a, n - 1) * a);
    else {
        T temp = qpow(a, n / 2);
        return temp * temp;
    }
}

template<typename T>
bool isPrime(T num) {
    if (num == 1 || num == 4)
        return false;
    if (num == 2 || num == 3)
        return true;
    if (num % 6 != 1 && num % 6 != 5)
        return false;
    T tmp = sqrt(num);
    for (T i = 5; i <= tmp; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

const int N = 1e7 + 100;
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


bool check(string const &s) {
    if (s.size() < 7)return false;
    for (int i = 0; i < s.size(); i++) {
        if ((i == 0 || i == 2 || i == 4 || i == 6) && (s[i] != 'a' && s[i] != '?')) {
            return false;
        }
        if ((i == 1 || i == 5) && (s[i] != 'b' && s[i] != '?')) {
            return false;
        }
        if ((i == 3) && (s[i] != 'c' && s[i] != '?')) {
            return false;
        }
    }
    return true;
}

auto solve() {
    map<string, bool> m;
    int n;
    string s;
    cin >> n;
    cin >> s;
    string _s = s;
    int cnt = 0;
    for (int i = 0; i < s.size() - 6; i++) {
        if (s.substr(i, 7) == "abacaba") {
            cnt++;
        }
    }
    if (cnt == 1) {
        for (auto &x: s) {
            if (x == '?')
                x = 'd';
        }
        cout << "Yes\n" << s << '\n';
        return;
    } else if (cnt >= 2) {
        cout << "No\n";
        return;
    }
    for (int i = 0; i < s.size() - 6; i++) {
        if (check(s.substr(i, 7))) {
            s.replace(i, 7, "abacaba");
            cnt = 0;
            for (int j = max(0, i - 7); j < min(int(s.size()), i + 8); j++) {
                if (s.substr(j, 7) == "abacaba") {
                    cnt++;
                }
            }
            if (cnt != 1) {
                s = _s;
                continue;
            }
            for (auto &x: s) {
                if (x == '?')x = 'd';
            }
            cout << "Yes\n";
            cout << s << '\n';
            return;
        }
    }
    cout << "No\n";
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}