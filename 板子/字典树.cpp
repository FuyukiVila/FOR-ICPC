#include <bits/stdc++.h>

//字典树

class Trie {
public:
    struct TrieNode {
        int wordCount;                //判断是否是单词
        std::map<char, TrieNode *> next;

        TrieNode() : wordCount(0)   //初始化
        {
            next = *new std::map<char, TrieNode *>;
        }
    };

    Trie() { root = new TrieNode(); }

    auto insert(const std::string &word, TrieNode *pos = nullptr) {
        auto location = (pos == nullptr) ? root : pos;
        for (char const &i: word) {
            if (location->next[i] == nullptr) {
                location->next[i] = new TrieNode();
            }
            location = location->next[i];
        }
        location->wordCount++;
        return location;
    }

    auto insert(const char &character, TrieNode *pos = nullptr) {
        auto location = (pos == nullptr) ? root : pos;
        if (location->next[character] == nullptr) {
            location->next[character] = new TrieNode();
        }
        location = location->next[character];
        location->wordCount++;
        return location;
    }

    auto search(const std::string &word, TrieNode *pos = nullptr) {
        auto location = (pos == nullptr) ? root : pos;
        for (int i = 0; i < word.length() && location; i++)
            location = location->next[word[i]];
        return location;
    }

    auto search(const char &character, TrieNode *pos = nullptr) {
        auto location = (pos == nullptr) ? root : pos;
        return location->next[character];
    }

    void deleteTrie(TrieNode *root) {
        for (auto &[_, node]: root->next) {
            if (node != nullptr) {
                deleteTrie(node);
            }
        }
        delete root;
    }

private:
    TrieNode *root;
};