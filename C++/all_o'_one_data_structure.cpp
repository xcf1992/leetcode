/*
 432. All O`one Data Structure

 Implement a data structure supporting the following operations:

 Inc(Key) - Inserts a new key with value 1. Or increments an existing key by 1. Key is guaranteed to be a non-empty string.
 Dec(Key) - If Key's value is 1, remove it from the data structure. Otherwise decrements an existing key by 1.
            If the key does not exist, this function does nothing. Key is guaranteed to be a non-empty string.
 GetMaxKey() - Returns one of the keys with maximal value. If no element exists, return an empty string "".
 GetMinKey() - Returns one of the keys with minimal value. If no element exists, return an empty string "".
 Challenge: Perform all these in O(1) time complexity.
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
#include <stdio.h>
#include <map>
#include <numeric>
using namespace std;

class Node {
public:
    string key = "";
    int val = 0;
    Node* prev = nullptr;
    Node* next = nullptr;

    Node(string s, int v, Node* n, Node* p) {
        key = s;
        val = v;
        next = n;
        prev = p;
    }

    void remove() {
        if (next != nullptr) {
            next -> prev = prev;
        }
        if (prev != nullptr) {
            prev -> next = next;
        }
    }

    bool add(Node* n) { // return if n's value is smaller than current node value
        if (n != nullptr and n -> val >= val) {
            n -> next = next;
            n -> prev = this;
            if (next != nullptr) {
                next -> prev = n;
            }
            next = n;
            return false;
        }
        if (n != nullptr and n -> val < val) {
            n -> next = this;
            n -> prev = prev;
            if (prev != nullptr) {
                prev -> next = n;
            }
            prev = n;
            return true;
        }
        return false;
    }

    pair<bool, bool> isHeadTail() {
        return make_pair(prev == nullptr, next == nullptr);
    }

    pair<bool, bool> insert() {
        val += 1;
        while (next != nullptr and next -> val < val) {
            Node* n = next;
            if (prev != nullptr) {
                prev -> next = n;
            }
            next -> prev = prev;

            prev = n;
            next = n -> next;

            if (next != nullptr) {
                next -> prev = this;
            }
            n -> next = this;
        }
        return isHeadTail();
    }

    pair<bool, bool> decrement() {
        val -= 1;
        if (prev != nullptr and prev -> val >= val) {
            Node* p = prev;
            if (next != nullptr) {
                next -> prev = p;
            }
            prev -> next = next;

            next = p;
            prev = p -> prev;

            if (prev != nullptr) {
                prev -> next = this;
            }
            p -> prev = this;
        }
        return isHeadTail();
    }
};

class AllOne {
private:
    map<string, Node*> allOneMap;
    Node* head = nullptr;
    Node* tail = nullptr;

    void replaceHeadTail(Node* n) {
        if (n == nullptr) {
            return;
        }

        pair<bool, bool> isHeadTail = n -> isHeadTail();
        if (isHeadTail.first) {
            head = n;
        }
        else if (n == head && !isHeadTail.first) {
            head = n->prev;
        }

        if (isHeadTail.second) {
            tail = n;
        }
        else if (n == tail && !isHeadTail.second) {
            tail = n->next;
        }
    }
public:
    /** Initialize your data structure here. */
    AllOne() {

    }

    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        if (allOneMap.find(key) == allOneMap.end()) {
            Node* n = new Node(key, 1, head, nullptr);
            if (head != nullptr) {
                if (head -> add(n)) {
                    head = n;
                }
            }
            else {
                tail = n;
                head = n;
            }
            allOneMap[key] = n;
        }
        else {
            allOneMap[key] -> insert();
            replaceHeadTail(allOneMap[key]);
        }
    }

    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        if (allOneMap.find(key) == allOneMap.end()) {
            return;
        }

        allOneMap[key] -> decrement();
        replaceHeadTail(allOneMap[key]);

        if (allOneMap[key] -> val < 1) {
            if (head == allOneMap[key]) {
                head = allOneMap[key] -> next;
                if (head != nullptr) {
                    head -> prev = nullptr;
                }
            }

            allOneMap[key] -> remove();
            delete allOneMap[key];
            allOneMap.erase(key);
        }
        return;
    }

    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        return tail == nullptr ? "" : tail -> key;
    }

    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        return head == nullptr ? "" : head -> key;
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne obj = new AllOne();
 * obj.inc(key);
 * obj.dec(key);
 * string param_3 = obj.getMaxKey();
 * string param_4 = obj.getMinKey();
 */
