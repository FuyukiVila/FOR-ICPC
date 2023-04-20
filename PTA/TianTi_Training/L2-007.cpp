#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
//字典树
const int Num = 2;             //每个节点需要保存26个字母
struct TrieNode {
    bool Isword;                //判断是否是单词
    TrieNode *next[Num]{};

    TrieNode() : Isword(false)   //初始化
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
    for (char i: word) {
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
    //while (word&&location)//注意location不能为空
    for (int i = 0; i < word.length() && location; i++)
        location = location->next[word[i] - '0'];
    return (location != nullptr && location->Isword);
}

void Trie::deleteTrie(TrieNode *root) {
    for (auto &i: root->next) {
        if (i != nullptr) {
            deleteTrie(i);
        }
    }
    delete root;
}

//字典树
inline int lowbit(int n) { return n & -n; }

template<typename T>
inline T qpow(T a, T n) {
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
bool isPrime(T num) {
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
        if (!st[i]) minp[i] = i, primes.emplace_back(i);
        for (int j = 0; primes[j] * i <= n; j++) {
            int t = primes[j] * i;
            st[t] = true;
            minp[t] = primes[j];
            if (i % primes[j] == 0) break;
        }
    }
}

struct family {
    double cnt_house;
    double square;

    family() : cnt_house(0), square(0) {}
};

struct node {
    string min_id{"99999"};
    int cnt{};
    double cnt_house{};
    double square{};

    bool operator<(const node &b) const {
        if (square / cnt == b.square / b.cnt) {
            return min_id < b.min_id;
        }
        return square / cnt > b.square / b.cnt;
    }
};

unordered_map<string, string> grp;
map<string, node> m;
map<string, family> f;
set<string> people;
set<node> ans;

string find(string a) {
    if (grp[a] == a) return a;
    return grp[a] = find(grp[a]);
}

auto solve() {
    int n;
    cin >> n;
    cout << fixed << setprecision(3);
    while (n--) {
        string id, father_id, mother_id;
        cin >> id >> father_id >> mother_id;
        vector<string> v;
        v.emplace_back(id);
        if (father_id != "-1")v.emplace_back(father_id);
        if (mother_id != "-1")v.emplace_back(mother_id);
        int k;
        cin >> k;
        for (int i = 1; i <= k; i++) {
            string son;
            cin >> son;
            v.emplace_back(son);
        }
        cin >> f[id].cnt_house >> f[id].square;
//        sort(v.begin(), v.end());
        for (const auto &x: v) {
            people.insert(x);
            if (grp.find(x) == grp.end())grp[x] = x;
            grp[find(x)] = find(v[0]);
        }
    }
    for (const auto &x: people) {
        m[find(x)].cnt++;
        m[find(x)].min_id = min(x, m[find(x)].min_id);
        m[find(x)].square += f[x].square;
        m[find(x)].cnt_house += f[x].cnt_house;
    }
    for (const auto &[i, j]: m) {
        ans.insert(j);
    }
    cout<<ans.size()<<'\n';
    for (const auto &[id, cnt, house, sq]: ans) {
        cout << id << ' ' << cnt << ' ' << house / cnt << ' ' << sq / cnt << '\n';
    }
}

signed main() {
    GKD
    auto T = 1;
//    cin >> T;
    while (T--) solve();
    return 0;
}