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
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
const int MAXN = 1e6 + 5;
struct node {
    int l, r;
    int maxn, minn;
} t[MAXN * 4];

//玩原神导致的
int n;
ll ans = 0;
int a[MAXN];

void build(int l = 1, int r = n, int p = 1) {
    t[p].l = l, t[p].r = r;
    if (l == r) {
        t[p].minn = a[l];
        t[p].maxn = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, p * 2), build(mid + 1, r, p * 2 + 1);
    t[p].maxn = max(t[p * 2].maxn, t[p * 2 + 1].maxn);
    t[p].minn = min(t[p * 2].minn, t[p * 2 + 1].minn);
}

pair<int, int> query(int l, int r, int p = 1) {
    if (l <= t[p].l && r >= t[p].r) {
        return {t[p].maxn, t[p].minn};
    }
    int mid = (t[p].l + t[p].r) / 2;
    int maxn = 0;
    int minn = INF;
    if (l <= mid) {
        maxn = max(query(l, r, p * 2).first, maxn);
        minn = min(query(l, r, p * 2).second, minn);
    }
    if (r > mid) {
        maxn = max(query(l, r, p * 2 + 1).first, maxn);
        minn = min(query(l, r, p * 2 + 1).second, minn);
    }
    return {maxn, minn};
}

int l[MAXN], r[MAXN];
int pos[MAXN];
bool vis[MAXN];

void genshin_start() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
//        a[i] = n - i + 1;
        pos[a[i]] = i;
        l[i + 1] = l[i];
        if (a[i] == i) {
            l[i + 1]++;
        } else {
            l[i + 1] = 0;
        }
    }

    for (int i = n; i >= 1; i--) {
        r[i - 1] = r[i];
        if (a[i] == i) {
            r[i - 1]++;
        } else {
            r[i - 1] = 0;
        }
    }
    build();
    for (int i = 1; i <= n; i++) {
        if (a[i] == i) {
            ans += 1 + r[i];
        } else {
            int p = i;
            int q = a[i];
            label:
            if (p > q)swap(p, q);
            if (vis[q]) {
                continue;
            } else {
                vis[q] = true;
            }
            auto que = query(p, q);
            int maxn = que.first, minn = que.second;
            if (minn != p || maxn != q) {
                if (p > minn) {
                    vis[q] = false;
                    p = minn;
                }
                if (q < maxn) {
                    q = maxn;
                }
                goto label;
            } else {
                ans += 1 + l[p] + r[q];
            }
        }
    }
    cout << ans << '\n';
}


signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}