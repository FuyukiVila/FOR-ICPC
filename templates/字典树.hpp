#ifndef __TRIE_HPP
#define __TRIE_HPP

#include "bits/stdc++.h"

template<class T = char>
class Trie {
private:
    typedef T element_type;

    struct TrieNode {
        int wordCount;
        std::map<char, std::shared_ptr<TrieNode> > next;

        TrieNode() : wordCount(0), next(std::map<element_type, std::shared_ptr<TrieNode> >()) {}

    };

    std::shared_ptr<TrieNode> _root;

public:

    Trie() { _root = std::make_shared<TrieNode>(); }

    std::shared_ptr<TrieNode> root() { return _root; }

    std::shared_ptr<TrieNode> begin() { return _root; }

    std::shared_ptr<TrieNode> end() { return nullptr; }

    void clear() { _root = std::make_shared<TrieNode>(); }

    template<class container>
    std::shared_ptr<TrieNode> insert(const container &word, std::shared_ptr<TrieNode> pos = nullptr) {
        static_assert(std::is_same<typename container::value_type, element_type>::value, "Container element type must be the same as ElementType");
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

    template<class container>
    std::shared_ptr<TrieNode> find(const container &word, std::shared_ptr<TrieNode> pos = nullptr) {
        static_assert(std::is_same<typename container::value_type, element_type>::value, "Container element type must be the same as ElementType");
        auto location = (pos == nullptr) ? _root : pos;
        for (int i = 0; i < word.length() && location; i++)
            location = location->next[word[i]];
        return location;
    }

    std::shared_ptr<TrieNode> find(element_type character, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        return location->next[character];
    }

    template<class container>
    size_t count(const container &word, std::shared_ptr<TrieNode> pos = nullptr) {
        static_assert(std::is_same<typename container::value_type, element_type>::value, "Container element type must be the same as ElementType");
        auto location = (pos == nullptr) ? _root : pos;
        for (int i = 0; i < word.length() && location; i++)
            location = location->next[word[i]];
        return location == nullptr ? 0 : location->wordCount;
    }

    size_t count(element_type character, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        return location->next[character] == nullptr ? 0 : location->next[character]->wordCount;
    }

};

#endif