/*
146. LRU Cache
https://leetcode.com/problems/lru-cache/

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
    CacheNode(int k, int v) : key(k), val(v), pre(nullptr), next(nullptr){};
};

class LRUCache {
private:
    unordered_map<int, CacheNode*> memo;
    int cap;
    int size;
    CacheNode *head;
public:
    LRUCache(int capacity) {
        if (capacity < 0) {
            return;
        }
        cap = capacity;
        size = 0;
        head = new CacheNode(-1, -1);
        head -> next = head;
        head -> pre = head;
    }

    int get(int key) {
        if (memo.find(key) == memo.end()) {
            return -1;
        }

        CacheNode* cur = memo[key];
        cur -> pre -> next = cur -> next;
        cur -> next -> pre = cur -> pre;

        cur -> next = head -> next;
        head -> next -> pre = cur;
        cur -> pre = head;
        head -> next = cur;
        return cur -> val;
    }

    void put(int key, int value) {
        if (cap < 1) {
            return;
        }

        if (memo.find(key) != memo.end()) {
            CacheNode* cur = memo[key];
            cur -> val = value;
            get(key);
            return;
        }

        CacheNode* newNode = new CacheNode(key, value);
        memo[key] = newNode;
        size += 1;

        newNode -> next = head -> next;
        head -> next -> pre = newNode;
        newNode -> pre = head;
        head -> next = newNode;
        if (size > cap) {
            size -= 1;
            CacheNode* removed = head -> pre;
            removed -> pre -> next = head;
            head -> pre = removed -> pre;
            memo.erase(removed -> key);
            delete removed;
        }
    }
};
