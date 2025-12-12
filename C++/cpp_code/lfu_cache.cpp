/*
460. LFU Cache
Design and implement a data structure for Least Frequently Used (LFU) cache.
It should support the following operations: get and put.

get(key)
Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.

put(key, value)
Set or insert the value if the key is not already present.
When the cache reaches its capacity,
it should invalidate the least frequently used item before inserting a new item.
For the purpose of this problem,
when there is a tie (i.e., two or more keys that have the same frequency),
the least recently used key would be evicted.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LFUCache cache = new LFUCache( 2  capacity  );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.get(3);       // returns 3.
cache.put(4, 4);    // evicts key 1.
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
using namespace std;

struct LFUNode {
    int freq_;
    int key_;
    int val_;
    LFUNode* prev_;
    LFUNode* next_;

    LFUNode(int f, int k, int v) {
        freq_ = f;
        key_ = k;
        val_ = v;
        prev_ = next_ = nullptr;
    }
};

class LFUCache {
private:
    int capacity_;
    int min_freq_;
    unordered_map<int, LFUNode*> key_to_node_;
    unordered_map<int, LFUNode*> freq_to_node_; // each freq would be a lRU list

public:
    LFUCache(int c) {
        capacity_ = c;
        min_freq_ = 1;
    }

    int get(int key) {
        if (key_to_node_.find(key) == key_to_node_.end()) {
            return -1;
        }

        LFUNode* cur = key_to_node_[key];
        LFUNode* prev_node = cur->prev_;
        LFUNode* next_node = cur->next_;
        if (prev_node != nullptr) {
            prev_node->next_ = next_node;
        }
        if (next_node != nullptr) {
            next_node->prev_ = prev_node;
        }
        // if there is only one node of the min_freq list
        if (min_freq_ == cur->freq_ and freq_to_node_[min_freq_]->next_ == freq_to_node_[min_freq_]) {
            freq_to_node_.erase(min_freq_);
            min_freq_ += 1;
        }

        cur->freq_ += 1;
        if (freq_to_node_.find(cur->freq_) == freq_to_node_.end()) {
            LFUNode* newHead = new LFUNode(cur->freq_, -1, -1);
            newHead->next_ = newHead;
            newHead->prev_ = newHead;
            freq_to_node_[cur->freq_] = newHead;
        }
        cur->next_ = freq_to_node_[cur->freq_]->next_;
        cur->next_->prev_ = cur;
        freq_to_node_[cur->freq_]->next_ = cur;
        cur->prev_ = freq_to_node_[cur->freq_];
        return cur->val_;
    }

    void put(int key, int value) {
        if (key_to_node_.find(key) != key_to_node_.end()) {
            key_to_node_[key]->val_ = value;
            get(key);
            return;
        }

        if (key_to_node_.size() == capacity_) {
            LFUNode* listHead = freq_to_node_[min_freq_];
            LFUNode* last = listHead->prev_;
            listHead->prev_ = last->prev_;
            last->prev_->next_ = listHead;
            key_to_node_.erase(last->key_);
            if (listHead->next_ == listHead) {
                freq_to_node_.erase(listHead->freq_);
            }
        }

        LFUNode* new_node = new LFUNode(1, key, value);
        min_freq_ = 1;
        key_to_node_[key] = new_node;
        if (freq_to_node_.find(min_freq_) == freq_to_node_.end()) {
            LFUNode* newHead = new LFUNode(min_freq_, -1, -1);
            newHead->next_ = newHead;
            newHead->prev_ = newHead;
            freq_to_node_[min_freq_] = newHead;
        }
        new_node->next_ = freq_to_node_[min_freq_]->next_;
        freq_to_node_[min_freq_]->next_->prev_ = new_node;
        new_node->prev_ = freq_to_node_[min_freq_];
        freq_to_node_[min_freq_]->next_ = new_node;
    }
};

/*
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */