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
    int freq;
    int key;
    int value;
    LFUNode* prev;
    LFUNode* next;

    LFUNode(int f, int k, int v) {
        freq = f;
        key = k;
        value = v;
        prev = next = nullptr;
    }
};

class LFUCache {
private:
    int capacity;
    int minFreq;
    unordered_map<int, LFUNode*> key2node;
    unordered_map<int, LFUNode*> freq2node;

public:
    LFUCache(int c) {
        capacity = c;
        minFreq = 1;
    }

    int get(int key) {
        if (key2node.find(key) == key2node.end()) {
            return -1;
        }

        LFUNode* cur = key2node[key];
        LFUNode* prevNode = cur->prev;
        LFUNode* nextNode = cur->next;
        if (prevNode != nullptr) {
            prevNode->next = nextNode;
        }
        if (nextNode != nullptr) {
            nextNode->prev = prevNode;
        }
        if (minFreq == cur->freq and freq2node[minFreq]->next == freq2node[minFreq]) {
            freq2node.erase(minFreq);
            minFreq += 1;
        }

        cur->freq += 1;
        if (freq2node.find(cur->freq) == freq2node.end()) {
            LFUNode* newHead = new LFUNode(cur->freq, -1, -1);
            newHead->next = newHead;
            newHead->prev = newHead;
            freq2node[cur->freq] = newHead;
        }
        cur->next = freq2node[cur->freq]->next;
        cur->next->prev = cur;
        freq2node[cur->freq]->next = cur;
        cur->prev = freq2node[cur->freq];
        return cur->value;
    }

    void put(int key, int value) {
        if (key2node.find(key) != key2node.end()) {
            key2node[key]->value = value;
            get(key);
            return;
        }

        if (key2node.size() == capacity) {
            LFUNode* listHead = freq2node[minFreq];
            if (listHead == nullptr) {
                // it will only happen when the capacity is 0
                return;
            }

            LFUNode* last = listHead->prev;
            listHead->prev = last->prev;
            last->prev->next = listHead;
            key2node.erase(last->key);
            if (listHead->next == listHead) {
                freq2node.erase(listHead->freq);
            }
        }

        LFUNode* newNode = new LFUNode(1, key, value);
        minFreq = 1;
        key2node[key] = newNode;
        if (freq2node.find(minFreq) == freq2node.end()) {
            LFUNode* newHead = new LFUNode(minFreq, -1, -1);
            newHead->next = newHead;
            newHead->prev = newHead;
            freq2node[minFreq] = newHead;
        }
        newNode->next = freq2node[minFreq]->next;
        freq2node[minFreq]->next->prev = newNode;
        newNode->prev = freq2node[minFreq];
        freq2node[minFreq]->next = newNode;
    }
};

/*
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */