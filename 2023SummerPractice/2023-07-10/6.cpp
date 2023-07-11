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

struct edge {
    int to;
    double t, c;
    double p;

    edge(int _to, int _t, int _c, double _p) : to(_to), t(_t), c(_c), p(_p) {}
};

constexpr int MAXN = 1e5 + 5;
vector<edge> e[MAXN];

struct node {
    double dis;
    int id;

    bool operator<(const node &a) const {
        return dis < a.dis;
    }
};

priority_queue<node> q;
double dis[MAXN];
bool vis[MAXN];

//玩原神导致的
void genshin_start() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        dis[i] = 1e18;
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        double t, p;
        double c;
        cin >> u >> v >> t >> p >> c;
        e[u].emplace_back(v, t, c, p);
    }
    dis[1] = 0;
    q.push({0, 1});
    while (!q.empty()) {
        int id = q.top().id;
        q.pop();
        if (vis[id])continue;
        vis[id] = true;
        for (auto i: e[id]) {
            double ti = 1.0 / (1.0 - i.p * 1.0 / 100);
            double gm = ti * (i.t + dis[id]) * 1.0;
            double hn = i.c * 1.0 + dis[id];
            if (gm > hn)gm = hn;
            if (dis[i.to] > gm) {
                dis[i.to] = gm;
                q.push({-dis[i.to], i.to});
                //dbg(dis[i.to],i.to,ti,i.tt,dis[w]);
            }
//            dbg(dis[to]);
        }
    }
    if (dis[n] == 1e18) {
        cout << -1 << '\n';
        return;
    }
    cout << fixed << setprecision(10);
    cout << dis[n] << '\n';
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}