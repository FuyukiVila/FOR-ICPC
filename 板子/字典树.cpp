#include <bits/stdc++.h>

//字典树
const int Num = 26;             //每个节点需要保存26个字母

class Trie {
public:
    struct TrieNode {
        bool Isword;                //判断是否是单词
        TrieNode *next[Num]{};

        TrieNode() : Isword(false)   //初始化
        {
            memset(next, 0, sizeof(next));
        }
    };

    Trie() { root = new TrieNode(); }

    void insert(const std::string &word) {
        TrieNode *location = root;
        for (char i: word) {
            if (location->next[i - 'a'] == nullptr) {
                auto *temp = new TrieNode();
                location->next[i - 'a'] = temp;
            }
            location = location->next[i - 'a'];
        }
        location->Isword = true;
    }

    bool search(std::string word) {
        TrieNode *location = root;
        //while (word&&location)//注意location不能为空
        for (int i = 0; i < word.length() && location; i++)
            location = location->next[word[i] - 'a'];
        return (location != nullptr && location->Isword);
    }

    void deleteTrie(TrieNode *root) {
        for (auto &i: root->next) {
            if (i != nullptr) {
                deleteTrie(i);
            }
        }
        delete root;
    }

private:
    TrieNode *root;
};