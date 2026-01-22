/*
https://leetcode.com/problems/lru-cache/
146. LRU Cache

Design and implement a data structure for Least Recently Used (LRU) cache.
It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present.
                  When the cache reached its capacity,
                  it should invalidate the least recently used item before inserting a new item.

The cache is initialized with a positive capacity.

Follow up:
Could you do both operations in O(1) time complexity?

Example:
LRUCache cache = new LRUCache( 2  capacity  );
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

struct CacheNode {
    CacheNode* pre;
    CacheNode* next;
    int key;
    int val;

    CacheNode(int k, int v) : key(k), val(v), pre(nullptr), next(nullptr) {};
};

class LRUCache {
private:
    unordered_map<int, CacheNode*> memo;
    int cap_;
    int cur_size_;
    CacheNode* list_head_;

public:
    LRUCache(int capacity) {
        if (capacity < 0) {
            return;
        }

        cap_ = capacity;
        cur_size_ = 0;
        list_head_ = new CacheNode(-1, -1);
        list_head_->next = list_head_;
        list_head_->pre = list_head_;
    }

    int get(int key) {
        if (memo.find(key) == memo.end()) {
            return -1;
        }

        CacheNode* cur = memo[key];
        cur->pre->next = cur->next;
        cur->next->pre = cur->pre;

        cur->next = list_head_->next;
        list_head_->next->pre = cur;
        cur->pre = list_head_;
        list_head_->next = cur;
        return cur->val;
    }

    void put(int key, int value) {
        if (cap_ < 1) {
            return;
        }

        if (memo.find(key) != memo.end()) {
            CacheNode* cur = memo[key];
            cur->val = value;
            get(key);
            return;
        }

        CacheNode* new_node = new CacheNode(key, value);
        memo[key] = new_node;
        cur_size_ += 1;

        new_node->next = list_head_->next;
        list_head_->next->pre = new_node;
        new_node->pre = list_head_;
        list_head_->next = new_node;
        if (cur_size_ > cap_) {
            cur_size_ -= 1;
            CacheNode* removed = list_head_->pre;
            removed->pre->next = list_head_;
            list_head_->pre = removed->pre;
            memo.erase(removed->key);
            delete removed;
        }
    }
};