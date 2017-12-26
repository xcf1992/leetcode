#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

struct CacheNode {
    CacheNode *pre;
    CacheNode *next;
    int key;
    int val;
    CacheNode(int k, int v) : key(k), val(v), pre(nullptr), next(nullptr){};
};

class LRUCache {
private:
    unordered_map<int, CacheNode*> map;
    int cap;
    int size;
    CacheNode *head;
    CacheNode *tail;

public:
    LRUCache(int capacity) {
        if (capacity < 0) {
            return;
        }
        map.clear();
        cap = capacity;
        size = 0;
        head = new CacheNode(-1, -1);
        tail = new CacheNode(-1, -1);
        head->next = tail;
        tail->pre = head;
    }

    int get(int key) {
        unordered_map<int, CacheNode*>::iterator it = map.find(key);
        if (it == map.end()) {
            return -1;
        }

        CacheNode *cur = it->second;
        cur->pre->next = cur->next;
        cur->next->pre = cur->pre;

        cur->next = head->next;
        head->next->pre = cur;
        cur->pre = head;
        head->next = cur;

        return cur->val;
    }

    void set(int key, int value) {
        if (cap < 1) {
            return;
        }

        unordered_map<int, CacheNode*>::iterator it = map.find(key);
        if (it != map.end()) {
            CacheNode *cur = it->second;
            cur->pre->next = cur->next;
            cur->next->pre = cur->pre;

            cur->next = head->next;
            head->next->pre = cur;
            cur->pre = head;
            head->next = cur;

            cur->val = value;
        }
        else {
            CacheNode *newNode = new CacheNode(key, value);

            newNode->next = head->next;
            head->next->pre = newNode;
            newNode->pre = head;
            head->next = newNode;
            size++;
			pair<int, CacheNode*> fuck(key, newNode);
            map.insert(fuck);

            if (size > cap) {
                size--;
                CacheNode *cur = tail->pre;
                cur->pre->next = tail;
                tail->pre = cur->pre;
                it = map.find(cur->key);
                map.erase(it);
                delete cur;
            }
        }
    }
};

int main() {
	LRUCache cache(1);
	cout << "1" << endl;

	cache.set(2,1);
	cout << "2" << endl;

	cache.get(2);
	cout << "3" << endl;

	cache.set(3,2);
	cout << "4" << endl;

	cache.get(2);
	cout << "5" << endl;

	cache.get(3);
	cout << "6" << endl;
	return 0;
}