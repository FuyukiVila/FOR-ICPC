#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;

template<typename T>
constexpr T qpow(T a, T n) {
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
constexpr bool isPrime(T num) {
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

constexpr int MAXN = 1e6 + 5;
int n, m;
int a[MAXN];

struct tree {
    int l{}, r{};
    ll value{};
    ll change_tag{0}, add_tag{0};
    bool is_change{false};

    constexpr void change(ll x) {
        add_tag = 0;
        change_tag = x;
        value = x;
        is_change = true;
    }
    
    constexpr void add(ll x) {
        value += x;
        if (is_change) {
            change_tag += x;
        } else {
            add_tag += x;
        }
    }
} t[MAXN * 4];

void build(int u = 1, int x = 1, int y = n) {
    t[u].l = x;
    t[u].r = y;
    if (x == y) {
        t[u].value = a[x];
        return;
    }
    int mid = (x + y) >> 1;
    build(u * 2, x, mid), build(u * 2 + 1, mid + 1, y);
    t[u].value = max(t[u * 2].value, t[u * 2 + 1].value);
}

void push_down(int u) {
    if (t[u].l == t[u].r)return;
    if (t[u].is_change) {
        t[u * 2].change(t[u].change_tag);
        t[u * 2 + 1].change(t[u].change_tag);
        t[u].is_change = false;
    } else if (t[u].add_tag) {
        t[u * 2].add(t[u].add_tag);
        t[u * 2 + 1].add(t[u].add_tag);
        t[u].add_tag = 0;
    }
}

void update(int l, int r, ll k, int op, int u = 1) {
    if (l <= t[u].l && r >= t[u].r) {
        if (op == 2) {
            t[u].add(k);
        } else if (op == 1) {
            t[u].change(k);
        }
        return;
    }
    push_down(u);
    int mid = (t[u].l + t[u].r) / 2;
    if (l <= mid) {
        update(l, r, k, op, u * 2);
    }
    if (r > mid) {
        update(l, r, k, op, u * 2 + 1);
    }
    t[u].value = max(t[u * 2].value, t[u * 2 + 1].value);
}

ll query(int l, int r, int u = 1) {
    if (l <= t[u].l && r >= t[u].r) {
        return t[u].value;
    }
    push_down(u);
    int mid = (t[u].l + t[u].r) / 2;
    ll res = -1e18;
    if (l <= mid) res = max(res, query(l, r, u * 2));
    if (r > mid) res = max(res, query(l, r, u * 2 + 1));
    return res;
}

auto genshin_start() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build();
    for (int i = 1; i <= m; i++) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 3) {
            cout << query(x, y) << '\n';
        } else {
            int k;
            cin >> k;
            update(x, y, k, op);
        }
//        for (int j = 1; j <= n; j++) {
//            cout << query(j, j) << ' ';
//        }
//        cout << '\n';
    }
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}