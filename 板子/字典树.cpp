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

    auto insert(const std::string &word) {
        TrieNode *location = root;
        for (char const &i: word) {
            if (location->next[i] == nullptr) {
                auto *temp = new TrieNode();
                location->next[i] = temp;
            }
            location = location->next[i];
        }
        location->wordCount++;
        return location;
    }

    auto search(std::string word) {
        TrieNode *location = root;
        for (int i = 0; i < word.length() && location; i++)
            location = location->next[word[i]];
        return location;
    }

    void deleteTrie(TrieNode *root) {
        for (auto &[i, j]: root->next) {
            if (j != nullptr) {
                deleteTrie(j);
            }
        }
        delete root;
    }

private:
    TrieNode *root;
};