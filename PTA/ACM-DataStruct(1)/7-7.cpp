#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
// 字典树
const int Num = 2; // 每个节点需要保存26个字母
struct TrieNode {
    bool Isword; // 判断是否是单词
    TrieNode *next[Num]{};

    TrieNode()
        : Isword(false) // 初始化
    {
        memset(next, 0, sizeof(next));
    }
};

class Trie {
  public:
    Trie() { root = new TrieNode(); }

    void insert(const string &word);

    bool search(string word);

    void deleteTrie(TrieNode *root);

  private:
    TrieNode *root;
};

void Trie::insert(const string &word) {
    TrieNode *location = root;
    for (char i : word) {
        if (location->next[i - '0'] == nullptr) {
            auto *temp = new TrieNode();
            location->next[i - '0'] = temp;
        }
        location = location->next[i - '0'];
    }
    location->Isword = true;
}

bool Trie::search(string word) {
    TrieNode *location = root;
    // while (word&&location)//注意location不能为空
    for (int i = 0; i < word.length() && location; i++)
        location = location->next[word[i] - '0'];
    return (location != nullptr && location->Isword);
}

void Trie::deleteTrie(TrieNode *root) {
    for (auto &i : root->next) {
        if (i != nullptr) {
            deleteTrie(i);
        }
    }
    delete root;
}

// 字典树
inline int lowbit(int n) { return n & -n; }

template <typename T> inline T qpow(T a, T n) {
    if (n == 0)
        return 1;
    else if (n % 2 == 1)
        return (qpow(a, n - 1) * a);
    else {
        T temp = qpow(a, n / 2);
        return temp * temp;
    }
}

template <typename T> bool isPrime(T num) {
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

struct node {
    char l, r;
    node(int _l = '#', int _r = '#') : l(_l), r(_r) {}
};

string s;
map<char, node> tree;
vector<char> ans;
int x = 0;
int cnt;
char init() {
    if (x >= s.size())
        return '#';
    if (s[x] == '#')
        return s[x];
    char tmp = s[x];
    ++x;
    tree[tmp].l = init();
    ++x;
    tree[tmp].r = init();
    return tmp;
}
void xianxu(char x) {
    if (x == '#')
        return;
    ans.push_back(x);
    if (tree[x].l == tree[x].r)
        cnt++;
    xianxu(tree[x].l);
    xianxu(tree[x].r);
}
void zhongxu(char x) {
    if (x == '#')
        return;
    zhongxu(tree[x].l);
    ans.push_back(x);
    zhongxu(tree[x].r);
}
void houxu(char x) {
    if (x == '#')
        return;
    houxu(tree[x].l);
    houxu(tree[x].r);
    ans.push_back(x);
}
auto solve() {
    cin >> s;
    init();
    xianxu(s[0]);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i];
    }
    if (s[0] == '#') {
        cout << 0 << '\n';
        return;
    }
    cout << '\n';
    ans.clear();
    zhongxu(s[0]);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i];
    }
    cout << '\n';
    ans.clear();
    houxu(s[0]);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i];
    }
    cout << '\n';
    cout << cnt;
}

signed main() {
    GKD auto T = 1;
    //    cin >> T;
    while (T--)
        solve();
    return 0;
}