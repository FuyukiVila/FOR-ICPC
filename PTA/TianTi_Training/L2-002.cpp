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

struct node {
    int num{};
    string next;
};
bool vis[100000];
map<string,node>a;

auto solve() {
    string pos;
    int n;
    cin >> pos >> n;
    for (int i = 1; i <= n; i++) {
        string address,next;
        int num;
        cin >> address >> num >> next;
        a[address].num = num;
        a[address].next = next;
    }
    vector<pair<string,node> > ans;
    vector<pair<string,node> > del;
    while (pos != "-1") {
        int num = a[pos].num;
        if (!vis[abs(num)]) {
            ans.emplace_back(pos, a[pos]);
            vis[abs(num)] = true;
        } else {
            del.emplace_back(pos, a[pos]);
        }
        pos = a[pos].next;
    }
    for(int i = 0;i<ans.size();i++){
        if(i==ans.size()-1)ans[i].second.next = "-1";
        else ans[i].second.next = ans[i+1].first;
        cout<<ans[i].first<<' '<<ans[i].second.num<<' '<<ans[i].second.next<<'\n';
    }
    for(int i = 0;i<del.size();i++){
        if(i==del.size()-1)del[i].second.next = "-1";
        else del[i].second.next = del[i+1].first;
        cout<<del[i].first<<' '<<del[i].second.num<<' '<<del[i].second.next<<'\n';
    }
}

signed main() {
    GKD
    auto T = 1;
//    cin >> T;
    while (T--) solve();
    return 0;
}