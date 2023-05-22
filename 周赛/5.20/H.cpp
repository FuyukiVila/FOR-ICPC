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

struct node {
    int id;
    int next;

    bool operator<(const node &b) const {
        return next < b.next;
    }
};

priority_queue<node> q;
bool is[300005];
int a[300005];
queue<int> v[300005];

auto solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        v[a[i]].push(i);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        v[a[i]].pop();
        if (is[a[i]]) continue;
        is[a[i]] = true;
        if (q.size() < k) q.push({a[i], v[a[i]].front()});
        else {
            is[q.top().id] = true;
            q.pop();
            ans++;
            q.push({a[i], v[a[i]].front()});
        }
    }
    cout << ans << '\n';
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) solve();
    return 0;
}