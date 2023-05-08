#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
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

auto solve() {
    int n, m;
    cin >> n >> m;
    int left = 0, right = 0;
    set<int> sit;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == -1) left++;
        else if (a[i] == -2)right++;
        else {
            sit.insert(a[i]);
        }
    }
    if (sit.empty()) {
        if (left && right) cout << min(m, max(left, right)) << '\n';
        else cout << min(n, m) << '\n';
        return;
    }
    if (!left) {
        cout << min(m, int(sit.size()) + right) << '\n';
    } else if (!right) {
        cout << min(m, int(sit.size()) + left) << '\n';
    } else {
        int ans = 0;
        vector<int> v;
        int siz = sit.size();
        v.push_back(0);
        for (auto x: sit) v.emplace_back(x);
        for (int i = 1; i < v.size(); i++) {
            ans = max(ans, siz + min(left, v[i] - 1 - (i - 1)) + min(right, m - v[i] - (siz - i)));
        }
        cout << min(max(max(ans, int(sit.size()) + left), int(sit.size()) + right), m) << '\n';
    }
}

signed main() {
    GKD
    auto T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}