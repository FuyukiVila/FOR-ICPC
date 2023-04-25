#include <bits/stdc++.h>

using namespace std;
using ll = long long;
bool a[505][505];
bool vis[505][505];
int num = 0;
string res;
bool hadfind = false;

struct node {
    int first;
    int second;

    bool operator<(const node &b) const {
        return first + second > b.first + b.second;
    }
    bool operator>(const node &b) const {
        return first + second < b.first + b.second;
    }
};

priority_queue<node> q;
priority_queue<node, vector<node>, greater<node> > pq;
int flag = 0;
int n;

bool check(int x1, int y1, int x2, int y2) {
    if (x1 > n || x1 < 1 || y1 > n || y1 < 1 || x2 > n || x2 < 1 || y2 > n || y2 < 1) return false;
    if (abs(x1 - x2) + abs(y1 - y2) >= n - 1)return true;
    else return false;
}

void dfs(int x, int y, string ans) {
    if (a[x][y] == false || hadfind) return;
    if (x == n && y == n) {
        hadfind = true;
        cout << "! " << ans << '\n';
        return;
    }
    dfs(x + 1, y, ans + 'D');
    dfs(x, y + 1, ans + 'R');
}

void solve() {
    cin >> n;
    for (int i = 2; i <= n; i += 2) {
        q.push({i, n - i + 1});
    }
    for (int i = 1; i <= n; i += 2) {
        q.push({i, n - i + 1});
    }
    while (!q.empty()) {
        auto x = q.top().first;
        auto y = q.top().second;
        q.pop();
        if (x + y != n + 1 && a[x][y + 1] == false && a[x + 1][y] == false) {
            a[x][y] = false;
            vis[x][y] = 1;
            continue;
        }
        if (!check(x, y, n, n) || vis[x][y])continue;
        vis[x][y] = 1;
        num++;
        assert(num <= 4 * n);
        cout << "? " << x << ' ' << y << ' ' << n << ' ' << n << endl;
        cout.flush();
        cin >> res;
        if (res == "NO") {
            a[x][y] = false;
        } else {
            a[x][y] = true;
            if (x == 1 && y == 2 || x == 2 && y == 1)break;
            q.push({x - 1, y});
            q.push({x, y - 1});
        }
    }
    for (int i = 1; i <= n; i++) {
        if (a[i][n - i + 1] == true) {
            pq.push({i, n - i + 2});
            pq.push({i + 1, n - i + 1});
        }
    }
    while (!pq.empty()) {
        auto x = pq.top().first;
        auto y = pq.top().second;
        pq.pop();
        if (a[x][y - 1] == false && a[x - 1][y] == false) {
            a[x][y] = false;
            vis[x][y] = 1;
            continue;
        }
        if (!check(x, y, 1, 1) || vis[x][y])continue;
        vis[x][y] = 1;
        num++;
        assert(num <= 4 * n);
        cout << "? " << 1 << ' ' << 1 << ' ' << x << ' ' << y << endl;
        cout.flush();
        cin >> res;
        if (res == "NO") {
            a[x][y] = false;
        } else {
            a[x][y] = true;
            if (x == n - 1 && y == n || x == n && y == n - 1)break;
            pq.push({x + 1, y});
            pq.push({x, y + 1});
        }
    }
    a[1][1] = true;
    a[n][n] = true;
//	for(int i = 1;i<=n;i++){
//		for(int j  = 1;j<=n;j++){
//			cout<<a[i][j];
//		}
//		cout<<'\n';
//	}
//	cout<<num<<'\n';
    dfs(1, 1, "");
}

signed main() {
    int T = 1;
    while (T--)solve();
    return 0;
}
