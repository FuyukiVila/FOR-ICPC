#include<bits/stdc++.h>

using namespace std;
const int maxn = 6e3 + 9;
//int g[6002][6002];
#define ll long long
unordered_map<int, int> Sqrt;

void solve(int C) {
    unordered_map<int, unordered_map<int, int>> g;
    cout << "Case #" << C << ":\n";
    int n, m;
    int x, y, w, k;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> x >> y >> w;
        g[x][y] = w;
    }
    int op;
    long long lastans = 0;
    while (m--) {
        cin >> op;
        cin >> x >> y;
        x = (x + lastans) % 6000 + 1;
        y = (y + lastans) % 6000 + 1;
        if (op == 1) {
            cin >> w;
            g[x][y] = w;
        }
        if (op == 2) {
            g[x].erase(y);
        }
        if (op == 3) {
            cin >> k >> w;
            for (int i = 1; i <= 6000; i++) {
                if (k < (x - i) * (x - i)) {
                    if (i < x) {
                        continue;
                    } else {
                        break;
                    }
                }
                if (Sqrt.find(k - (x - i) * (x - i)) == Sqrt.end()) continue;
                int dis = Sqrt[k - (x - i) * (x - i)];
                if (dis == 0) {
                    if (g[i].find(y) != g[i].end()) g[i][y] += w;
                    continue;
                }
                if (g[i].find(y + dis) != g[i].end()) g[i][y + dis] += w;
                if (g[i].find(y - dis) != g[i].end()) g[i][y - dis] += w;
            }
        }
        if (op == 4) {
            cin >> k;
            long long ans = 0;
            for (int i = 1; i <= 6000; i++) {
                if (k < (x - i) * (x - i)) {
                    if (i < x) {
                        continue;
                    } else {
                        break;
                    }
                }
                if (Sqrt.find(k - (x - i) * (x - i)) == Sqrt.end()) continue;
                int dis = Sqrt[k - (x - i) * (x - i)];
                if (dis == 0) {
                    if (g[i].find(y) != g[i].end()) ans += g[i][y];
                    continue;
                }
                if (g[i].find(y - dis) != g[i].end()) ans += g[i][y - dis];
                if (g[i].find(y + dis) != g[i].end()) ans += g[i][y + dis];
            }
            lastans = ans;
            cout << ans << '\n';
        }
    }
}

void init() {
    for (int i = 0; i <= 6000; i++) {
        Sqrt[i * i] = i;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init();
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) solve(i);
    return 0;
}
