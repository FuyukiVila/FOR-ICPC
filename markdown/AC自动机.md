# AC自动机

- **maxsize ：模式串的总长**

```cpp
#ifndef __AUTOMATON_HPP
#define __AUTOMATON_HPP

#include "bits/stdc++.h"

template<size_t base = 26>
class Automaton {
private:
    std::array<std::vector<int>, base> tr;
    std::vector<int> count;
    std::vector<int> fail;
    int tot = 0;
public:
    // MAXSIZE 模式串的总长
    Automaton(int maxsize) : count(maxsize), fail(maxsize) {
        for (int i = 0; i < base; ++i) tr[i].resize(maxsize);
    }

    void insert(const std::string &s, int id) {
        int u = 0;
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            if (!tr[c][u]) tr[c][u] = ++tot;
            u = tr[c][u];
        }
        count[u] = id;
    }

    void build() {
        std::queue<int> q;
        for (int i = 0; i < base; i++) if (tr[i][0]) q.push(tr[i][0]);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < base; i++) {
                if (tr[i][u]) {
                    fail[tr[i][u]] = tr[i][fail[u]];
                    q.push(tr[i][u]);
                } else tr[i][u] = tr[i][fail[u]];
            }
        }
    }

    std::unordered_map<int, int> query(const std::string &t) {
        int u = 0;
        std::unordered_map<int, int> ans;
        for (int i = 0; i < t.size(); i++) {
            u = tr[t[i] - 'a'][u];
            for (int j = u; j; j = fail[j]) {
                if (count[j]) ans[count[j]]++;
            }
        }
        return ans;
    }
};


#endif
```

