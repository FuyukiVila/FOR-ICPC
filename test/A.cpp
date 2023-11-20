#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

#define dbg(x...)                                                              \
    do {                                                                       \
        std::cout << #x << " -> ";                                             \
        err(x);                                                                \
    } while (0)

void err() { std::cout << std::endl; }

template<class T, class... Ts>
void err(T arg, Ts &...args) {
    std::cout << arg << ' ';
    err(args...);
}

using namespace std;
using ll = long long;
using ull = unsigned long long;
template<typename T, typename K> using umap = unordered_map<T, K>;
template<class T> using uset = unordered_set<T>;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
ll mod = 0;

ll qpow(ll _a, ll _n, ll _mod = mod) {
    ll ans = 1;
    while (_n) {
        if (_n & 1)
            ans *= _a;
        _n >>= 1;
        _a *= _a;
        if (_mod > 0) {
            ans %= _mod;
            _a %= _mod;
        }
    }
    return ans;
}

constexpr int N = 1e7 + 100;
int minp[N];
vector<int> primes;
bool st[N];

void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i])
            minp[i] = i, primes.emplace_back(i);
        for (int j = 0; primes[j] * i <= n; j++) {
            int t = primes[j] * i;
            st[t] = true;
            minp[t] = primes[j];
            if (i % primes[j] == 0)
                break;
        }
    }
}

std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_int_distribution<ll> ranint(1, 1e18);

// 玩原神导致的
#define x first
#define y second

//struct node {
//    string mp;
//    int id;
//    bool dir;
//
//    node(char **a, int id, bool dir) {
//        for (int i = 1; i <= 6; i++) {
//            for (int j = 1; j <= 6; j++) {
//                this->mp += a[i][j];
//            }
//        }
//        this->id = id;
//        this->dir = dir;
//    }
//};

//map<node, bool> vis;
int num = 0;

struct car {
    int id;
    vector<pair<int, int>> location;
    //横的为0,竖的为1
    bool direction;

    void init() {
        sort(location.begin(), location.end());
        if (location[0].x == location[1].x) {
            direction = 0;
        } else {
            direction = 1;
        }
    }

    void up() {
        for (auto &loc: location) {
            loc.x--;
        }
    }

    void down() {
        for (auto &loc: location) {
            loc.x++;
        }
    }

    void left() {
        for (auto &loc: location) {
            loc.y--;
        }
    }

    void right() {
        for (auto &loc: location) {
            loc.y++;
        }
    }

    void move(int n) {
        if (direction) {
            if (n) {
                down();
            } else {
                up();
            }
        } else {
            if (n) {
                right();
            } else {
                left();
            }
        }
    }

};

int pengzhuang(vector<car> now, int id) {
    for (int i = 1; i <= num; i++) {
        if (i == id) continue;
        for (auto a: now[id].location) {
            for (auto b: now[i].location) {
                if (a == b) {
                    return i;
                }
            }
        }
    }
    return 0;
}

bool zhuangqiang(vector<car> now, int id) {
    if (id != 1) {
        for (auto a: now[id].location) {
            if (a.x > 6 || a.x < 1 || a.y < 1 || a.y > 6) {
                return true;
            }
        }
    } else if (id == 1) {
        for (auto a: now[id].location) {
            if (a.x > 6 || a.x < 1 || a.y < 1) {
                return true;
            }
        }
    }
    return false;
}

bool exit(vector<car> now) {
    for (auto const &a: now[1].location) {
        if (a.y <= 6) {
            return false;
        }
    }
    return true;
}

int ans = 11;

void dfs(vector<car> now, int step) {
    if (exit(now)) {
        ans = min(ans, step - 1);
        return;
    }
    int w = 0;
    for (int i = 2; i <= num; i++) {
        for (auto &[x, y]: now[i].location) {
            if (x == 3 && y >= now[1].location[0].y) {
                w++;
                break;
            }
        }
    }
    if (w == 0) {
        ans = min(ans, step + (6 - now[1].location[0].y));
        return;
    }
    if (step + (6 - now[1].location[0].y) >= ans) {
        return;
    }
    for (int i = 1; i <= num; i++) {
        now[i].move(0);
        if (!pengzhuang(now, i) && !zhuangqiang(now, i)) {
            dfs(now, step + 1);
        }
        now[i].move(1);
        now[i].move(1);
        if (!pengzhuang(now, i) && !zhuangqiang(now, i)) {
            dfs(now, step + 1);
        }
        now[i].move(0);
    }
}

void genshin_start() {
    auto a = new int[7][7];
    vector<car> c(15);
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            cin >> a[i][j];
            num = max(num, a[i][j]);
            if (a[i][j]) {
                c[a[i][j]].location.emplace_back(i, j);
            }
        }
    }
    for (int i = 1; i <= num; i++) {
        if (c[i].location.size() > 1) {
            c[i].init();
            c[i].id = i;
        }
    }
    if (c[1].direction == 1) {
        cout << -1 << '\n';
        return;
    }
    if (c[1].location[0].x != 3) {
        cout << -1 << '\n';
        return;
    }
    for (int i = 2; i <= num; i++) {
        if (c[i].location[0].x == c[1].location[0].x && c[i].direction == 0) {
            cout << -1 << '\n';
            return;
        }
    }
    dfs(c, 1);
    if (ans == 11) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--)
        genshin_start();
    return 0;
}