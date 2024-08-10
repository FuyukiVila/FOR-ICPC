#ifndef __TRIE_HPP
#define __TRIE_HPP

#include "bits/stdc++.h"

template<class T = char>
class Trie {
private:
    typedef T element_type;

    struct TrieNode {
        size_t wordCount;
        std::map<element_type, std::shared_ptr<TrieNode> > next;

        TrieNode() : wordCount(0), next(std::map<element_type, std::shared_ptr<TrieNode> >()) {}

    };

    std::shared_ptr<TrieNode> _root;

public:

    explicit Trie() { _root = std::make_shared<TrieNode>(); }

    std::shared_ptr<TrieNode> root() { return _root; }

    void clear() { _root = std::make_shared<TrieNode>(); }

    std::shared_ptr<TrieNode> insert(const std::basic_string<element_type> &word, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        for (char const &i: word) {
            if (location->next[i] == nullptr) {
                location->next[i] = std::make_shared<TrieNode>();
            }
            location = location->next[i];
        }
        location->wordCount++;
        return location;
    }

    std::shared_ptr<TrieNode> insert(element_type character, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        if (location->next[character] == nullptr) {
            location->next[character] = std::make_shared<TrieNode>();
        }
        location = location->next[character];
        location->wordCount++;
        return location;
    }

    std::shared_ptr<TrieNode> find(const std::basic_string<element_type> &word, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        for (int i = 0; i < word.length() && location; i++)
            location = location->next[word[i]];
        return location;
    }

    std::shared_ptr<TrieNode> find(element_type character, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        return location->next[character];
    }

    size_t count(const std::basic_string<element_type> &word, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        for (int i = 0; i < word.length() && location; i++)
            location = location->next[word[i]];
        return location == nullptr ? 0 : location->wordCount;
    }

    size_t count(element_type character, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        return location->next[character] == nullptr ? 0 : location->next[character]->wordCount;
    }

    std::shared_ptr<TrieNode> erase(const std::basic_string<element_type> &word, std::shared_ptr<TrieNode> pos = nullptr, size_t count = 1) {
        auto location = (pos == nullptr) ? _root : pos;
        for (int i = 0; i < word.length() && location; i++)
            location = location->next[word[i]];
        if (location == nullptr) return nullptr;
        location->wordCount -= min(count, location->wordCount);
        return location;
    }

    std::shared_ptr<TrieNode> erase(element_type character, std::shared_ptr<TrieNode> pos = nullptr, size_t count = 1) {
        auto location = (pos == nullptr) ? _root : pos;
        if (location->next[character] == nullptr) return nullptr;
        location->next[character]->wordCount -= min(count, location->next[character]->wordCount);
        return location;
    }

};

#endif