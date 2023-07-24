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

struct edge {
    int to;
    bool v{false};

    edge(int _to) : to{_to} {}
};

set<pair<int, int>> s;

vector<edge> e[1000005];
vector<int> e1[1000005];
vector<int> e2[1000005];
int in1[1000005];
int in2[1000005];
bool flag = false;
int n, m;
bool vis[1000005];

bool toposort_1() {
    vector<int> L;
    queue<int> S;
    for (int i = 1; i <= n; i++) {
        if (in1[i] == 0) {
            S.push(i);
        }
    }
    while (!S.empty()) {
        int u = S.front();
        S.pop();
        L.push_back(u);
        for (auto v: e1[u]) {
            if (--in1[v] == 0) {
                S.push(v);
            }
        }
    }
    if (L.size() == n) {
        cout << 1 << '\n';
        for (auto x: L) {
            cout << x << ' ';
        }
        cout << '\n';
        return true;
    }
    return false;
//    for (auto const &x: L) {
//        cout << x << ' ';
//    }
//    cout << '\n';
}

//void toposort_2() {
//    vector<int> L;
//    queue<int> S;
//    for (int i = 1; i <= n; i++) {
//        if (in2[i] == 0) {
//            S.push(i);
//        }
//    }
//    while (!S.empty()) {
//        int u = S.front();
//        S.pop();
//        L.push_back(u);
//        for (auto v: e2[u]) {
//            if (--in2[v] == 0) {
//                S.push(v);
//            }
//        }
//    }
//    for (auto const &x: L) {
//        cout << x << ' ';
//    }
//    cout << '\n';
//}

void dfs(int i) {
    for (auto &[x, v]: e[i]) {
        if (v) {
            continue;
        }
        v = true;
        if (vis[x]) {
            flag = true;
            e2[i].emplace_back(x);
            in1[x]--;
            in2[x]++;
        } else {
            vis[x] = true;
            e1[i].emplace_back(x);
            dfs(x);
            vis[x] = false;
        }
    }
}

auto genshin_start() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (s.find(make_pair(u, v)) != s.end()) {
            continue;
        }
        s.insert({u, v});
        e1[u].emplace_back(v);
        in1[v]++;
    }
//    for (int i = 1; i <= n; i++) {
//        vis[i] = true;
//        dfs(i);
//        vis[i] = false;
//    }
//    if (flag) {
//        cout << 2 << '\n';
//    } else {
//        cout << 1 << '\n';
//    }
    if (!toposort_1()) {
        cout << 2 << '\n';
        for (int i = 1; i <= n; i++) {
            cout << i << " \n"[i == n];
        }
        for (int i = n; i >= 1; i--) {
            cout << i << " \n"[i == 1];
        }
    }
//    if (flag) {
//        toposort_2();
//    }
}

signed main() {
    GKD;
    auto T{1};
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}