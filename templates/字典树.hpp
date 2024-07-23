#ifndef __TRIE_HPP
#define __TRIE_HPP

#include "bits/stdc++.h"

class Trie {
private:
    struct TrieNode {
        int wordCount;
        std::map<char, std::shared_ptr<TrieNode> > next;

        TrieNode() : wordCount(0) {}

    };

    std::shared_ptr<TrieNode> root;

public:

    Trie() { root = std::make_shared<TrieNode>(); }

    std::shared_ptr<TrieNode> getRoot() { return root; }

    std::shared_ptr<TrieNode> insert(const std::string &word, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? root : pos;
        for (char const &i: word) {
            if (location->next[i] == nullptr) {
                location->next[i] = std::make_shared<TrieNode>();
            }
            location = location->next[i];
        }
        location->wordCount++;
        return location;
    }

    std::shared_ptr<TrieNode> insert(const char &character, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? root : pos;
        if (location->next[character] == nullptr) {
            location->next[character] = std::make_shared<TrieNode>();
        }
        location = location->next[character];
        location->wordCount++;
        return location;
    }

    std::shared_ptr<TrieNode> search(const std::string &word, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? root : pos;
        for (int i = 0; i < word.length() && location; i++)
            location = location->next[word[i]];
        return location;
    }

    std::shared_ptr<TrieNode> search(const char &character, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? root : pos;
        return location->next[character];
    }

};

#endif