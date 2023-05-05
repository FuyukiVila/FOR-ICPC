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

int grp[10004];

int find(int n) {
    if (grp[n] == n)return n;
    else return grp[n] = find(grp[n]);
}

auto solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        grp[i] = i;
    }
    while (true) {
        char c;
        int x, y;
        cin >> c;
        if (c == 'S')break;
        else if (c == 'I') {
            cin >> x >> y;
            grp[find(x)] = find(y);
        } else {
            cin >> x >> y;
            if (find(x) == find(y))cout << "yes\n";
            else cout << "no\n";
        }
    }
    set<int> ans;
    for (int i = 1; i <= n; i++) {
        ans.insert(find(i));
    }
    if (ans.size() == 1)cout << "The network is connected.";
    else cout << "There are " << ans.size() << " components.";
}

signed main() {
    GKD
    auto T = 1;
//    cin >> T;
    while (T--) solve();
    return 0;
}