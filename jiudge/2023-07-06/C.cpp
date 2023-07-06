
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
    int cnt, p;
} a1[100005], a2[100005];
int n, c, d, cnt1, cnt2, k[100005];
int ans1 = -1, ans2 = -1;

int lowbit(int x) {
    return x & -x;
}

void update(int x, int y, int val) {
    while (x < y) {
        k[x] = max(k[x], val);
        x += lowbit(x);
    }
}

int query(int x) {
    int ans = 0;
    while (x > 0) {
        ans = max(ans, k[x]);
        x -= lowbit(x);
    }
    return ans;
}

auto solve() {
    cin >> n >> c >> d;
    for (int i = 0; i < n; i++) {
        int b, p;
        char s;
        cin >> b >> p >> s;
        if (s == 'C') {
            if (p <= c) {
                a1[cnt1].cnt = b;
                a1[cnt1++].p = p;
                ans1 = max(ans1, b);
            }
        } else {
            if (p <= d) {
                a2[cnt2].cnt = b;
                a2[cnt2++].p = p;
                ans2 = max(ans2, b);
            }
        }
    }
    int ans = 0;
    if (ans1 != -1 && ans2 != -1) {
        ans = ans1 + ans2;
    }
    clr(k, 0);
    for (int i = 0; i < cnt1; i++) {
        int tot = query(c - a1[i].p);
        if (tot > 0) {
            ans = max(ans, tot + a1[i].cnt);
        }
        update(a1[i].p, 100005, a1[i].cnt);
    }
    clr(k, 0);
    for (int i = 0; i < cnt2; i++) {
        int tot = query(d - a2[i].p);
        if (tot > 0) {
            ans = max(ans, tot + a2[i].cnt);
        }
        update(a2[i].p, 100005, a2[i].cnt);
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