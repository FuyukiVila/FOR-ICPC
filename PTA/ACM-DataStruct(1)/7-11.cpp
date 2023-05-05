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
int g[10004];

int find(int x) {
    if (g[x] == x)return x;
    else return g[x] = find(g[x]);
}

auto solve() {
    int n;
    cin >> n;
    set<int> people;
    set<int> community;
    for (int i = 1; i <= n; i++)g[i] = i;
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        for (int j = 1; j <= k; j++) {
            int m;
            cin >> m;
            people.insert(m);
            if (grp[m] == 0)grp[m] = i;
            else {
                g[find(grp[m])] = find(i);
                grp[m] = i;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        community.insert(find(i));
    }
    cout << people.size() << ' ' << community.size() << '\n';
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (find(grp[x]) == find(grp[y]))cout << "Y\n";
        else cout << "N\n";
    }
}

signed main() {
    GKD
    auto T = 1;
//    cin >> T;
    while (T--) solve();
    return 0;
}