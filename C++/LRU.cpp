#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct CacheNode {
    int key;
    int value;
    CacheNode *next;
    CacheNode *previous;
    CacheNode(int _k, int _v): key(_k), value(_v), next(nullptr), previous(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    int num;
    CacheNode *head;
    CacheNode *tail;
    unordered_map<int, CacheNode*> listMap;

public:
    LRUCache(int _c) {
        if (_c <= 0) {
            return;
        }
        capacity = _c;
        int num = 0;
        head = new CacheNode(-1, -1);
        tail = new CacheNode(-1, -1);
        head->next = tail;
        tail->previous = head;
    }

    int get(int key) {
        if (num == 0) {
            return -1;
        }
        if (listMap.find(key) == listMap.end()) {
            return -1;
        }

        CacheNode *visit = listMap[key];
        visit->previous->next = visit->next;
        visit->next->previous = visit->previous;

        visit->next = head->next;
        head->next->previous = visit;
        visit->previous = head;
        head->next = visit;

        return visit->value;
    }

    void set(int key, int value) {
        if (capacity <= 0) {
            return ;
        }
        if (listMap.find(key) != listMap.end()) {
            CacheNode *visit = listMap[key];
            visit->value = value;

            visit->previous->next = visit->next;
            visit->next->previous = visit->previous;

            visit->next = head->next;
            head->next->previous = visit;
            visit->previous = head;
            head->next = visit;
        }
        else {
            CacheNode *newNode = new CacheNode(key, value);

            newNode->next = head->next;
            head->next->previous = newNode;
            newNode->previous = head;
            head->next = newNode;
			pair<int, CacheNode*> fuck(key, newNode);
            listMap.insert(fuck);
            num++;

            if (num > capacity) {
                num--;
                CacheNode *cur = tail->previous;
                cur->previous->next = tail;
                tail->previous = cur->previous;

                listMap.erase(cur->key);
                delete cur;
            }
        }

        return ;
    }
};

int main() {
	class LRUCache lru(2);
	lru.set(2, 1);
	cout << lru.get(2) << endl;
	string s = "1";
	s = s.substr(1, 0);
	return 0;

}