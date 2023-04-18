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
struct TrieNode
{
    bool Isword; // 判断是否是单词
    TrieNode *next[Num]{};

    TrieNode() : Isword(false) // 初始化
    {
        memset(next, 0, sizeof(next));
    }
};

class Trie
{
public:
    Trie() { root = new TrieNode(); }

    void insert(const string &word);

    bool search(string word);

    void deleteTrie(TrieNode *root);

private:
    TrieNode *root;
};

void Trie::insert(const string &word)
{
    TrieNode *location = root;
    for (char i : word)
    {
        if (location->next[i - '0'] == nullptr)
        {
            auto *temp = new TrieNode();
            location->next[i - '0'] = temp;
        }
        location = location->next[i - '0'];
    }
    location->Isword = true;
}

bool Trie::search(string word)
{
    TrieNode *location = root;
    // while (word&&location)//注意location不能为空
    for (int i = 0; i < word.length() && location; i++)
        location = location->next[word[i] - '0'];
    return (location != nullptr && location->Isword);
}

void Trie::deleteTrie(TrieNode *root)
{
    for (auto &i : root->next)
    {
        if (i != nullptr)
        {
            deleteTrie(i);
        }
    }
    delete root;
}

// 字典树
inline int lowbit(int n) { return n & -n; }

template <typename T>
inline T qpow(T a, T n)
{
    if (n == 0)
        return 1;
    else if (n % 2 == 1)
        return (qpow(a, n - 1) * a);
    else
    {
        T temp = qpow(a, n / 2);
        return temp * temp;
    }
}

template <typename T>
bool isPrime(T num)
{
    if (num == 1 || num == 4)
        return false;
    if (num == 2 || num == 3)
        return true;
    if (num % 6 != 1 && num % 6 != 5)
        return false;
    T tmp = sqrt(num);
    for (T i = 5; i <= tmp; i += 6)
    {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

const int N = 1e7 + 100;
int minp[N];
vector<int> primes;
bool st[N];

void get_primes(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (!st[i])
            minp[i] = i, primes.emplace_back(i);
        for (int j = 0; primes[j] * i <= n; j++)
        {
            int t = primes[j] * i;
            st[t] = true;
            minp[t] = primes[j];
            if (i % primes[j] == 0)
                break;
        }
    }
}

struct edge
{
    int to;
    int weight;

    template <class T>
    edge(T _to, T _weight)
    {
        to = _to;
        weight = _weight;
    }
};

const int maxn = 100005;

struct node
{
    int dis{};
    int id{};
    int max_v{}, min_v = INF;

    bool operator<(const node &b) const
    {
        return dis > b.dis;
    }
} d[maxn];

int value[maxn];
int in[maxn];
bool vis[maxn];

int minn[maxn];
int dp[maxn];
stack<int> stk;
bool is[maxn];
// instk:是否在栈中  scc:每个点所属的强连通分量编号  cscc:强连通分量的数量 sz:强连通分量的大小
int dfsn[maxn], low[maxn], instk[maxn], scc[maxn], dfsncnt = 0, cscc = 0, sz[maxn];
vector<vector<int>> e(maxn);
vector<pair<int, int>> road;
vector<int> new_edge[maxn];
void tarjan(int p)
{
    low[p] = dfsn[p] = ++dfsncnt;
    instk[p] = 1;
    stk.push(p);
    for (auto q : e[p])
    {
        if (!dfsn[q])
        {
            tarjan(q);
            low[p] = min(low[p], low[q]);
        }
        else if (instk[q])
        {
            low[p] = min(low[p], dfsn[q]);
        }
    }
    if (low[p] == dfsn[p])
    {
        int top;
        cscc++;
        do
        {
            top = stk.top();
            stk.pop();
            instk[top] = 0;
            scc[top] = cscc;
            sz[cscc]++;
        } while (top != p);
    }
}

auto solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> value[i];
    }
    for (int i = 1; i <= m; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        if (z == 1)
        {
            road.emplace_back(x, y);
            e[x].push_back(y);
        }
        else
        {
            road.emplace_back(x, y);
            road.emplace_back(y, x);
            e[y].push_back(x);
            e[x].push_back(y);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (!dfsn[i])
        {
            tarjan(i);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        d[scc[i]].id = scc[i];
        d[scc[i]].max_v = max(d[scc[i]].max_v, value[i]);
        d[scc[i]].min_v = min(d[scc[i]].min_v, value[i]);
    }
    for (auto x : road)
    {
        int u = x.first, v = x.second;
        if (scc[u] == scc[v])
            continue;
        new_edge[scc[u]].push_back(scc[v]);
        in[scc[v]]++;
    }
    int start = scc[1], end = scc[n];
    //    for(int i = 1;i<=n;i++){
    //        cout<<scc[i]<<" \n"[i==n];
    //    }
    queue<int> S;
    vector<int> L;
    static vector<int> level(cscc + 1, 0);
    for (int i = 1; i <= cscc; i++)
    {
        if (!in[i])
            S.push(i);
        while (!S.empty())
        {
            int u = S.front();
            S.pop();
            L.push_back(u);
            level[u] = L.size();
            for (auto v : new_edge[u])
            {
                if (--in[v] == 0)
                {
                    S.push(v);
                }
            }
        }
    }
    for (auto x : new_edge[start])
        is[x] = true;
    clr(minn, INF);
    is[start] = true;
    for (auto x : L)
    {
        if (!is[x])
            continue;
        dp[x] = max(dp[x], d[x].max_v - d[x].min_v);
        minn[x] = min(minn[x], d[x].min_v);
        for (auto y : new_edge[x])
        {
            minn[y] = min(min(minn[x], minn[y]), d[y].min_v);
            dp[y] = max(max(dp[y], d[y].max_v - minn[y]), dp[x]);
            is[y] = true;
        }
        //        cout<<x<<' ';
    }
    cout << dp[end];
}

signed main()
{
    GKD auto T = 1;
    //    cin >> T;
    while (T--)
        solve();
    return 0;
}