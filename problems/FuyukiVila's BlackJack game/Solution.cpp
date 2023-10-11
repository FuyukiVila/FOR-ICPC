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
template<typename T>
using umap = unordered_map<T, T>;
template<class T>
using uset = unordered_set<T, T>;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;

struct player {

    vector<int> cards;

    constexpr int get_value() const {
        int maxn = 0;
        auto const &dfs = [&](auto const &dfs, int i = 0, int value = 0) -> void {
            if (i == cards.size()) {
                if (value <= 21) {
                    maxn = max(maxn, value);
                }
                return;
            }
            dfs(dfs, i + 1, value + cards[i]);
            if (cards[i] == 1) {
                dfs(dfs, i + 1, value + 11);
            }
        };
        dfs(dfs);
        return maxn;
    }

    void draw(queue<int> &q) {
        int card = q.front();
        q.pop();
        cards.emplace_back(card);
    }
};

auto genshin_start() {
    int n{}, m{};
    int y{};
    cin >> n >> m;
    vector<player> p(n + 1);
    queue<int> deck;
    for (int i = 0; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        p[i].cards.emplace_back(a);
        p[i].cards.emplace_back(b);
    }
    y = p[0].cards[1];
    if (y == 1) y = 11;
    for (int i = 1; i <= m; i++) {
        int c;
        cin >> c;
        deck.push(c);
    }
    for (int i = 1; i <= n; i++) {
        while (p[i].cards.size() < 5) {
            int value = p[i].get_value();
            if (value >= 20 || value >= y + 10 || value == 0) {
                break;
            } else {
                p[i].draw(deck);
            }
        }
    }
    while (p[0].cards.size() < 5 && p[0].get_value() < 17 && p[0].get_value() != 0) {
        p[0].draw(deck);
    }
    int value = p[0].get_value();
    for (int i = 1; i <= n; i++) {
        int myValue = p[i].get_value();
        if (myValue < value) {
            cout << "lose\n";
        } else if (myValue == value) {
            cout << "draw\n";
        } else {
            cout << "win\n";
        }
    }
}

signed main() {
    GKD;
    auto T{1};
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}