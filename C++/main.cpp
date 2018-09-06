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

struct myComp {
    bool operator() (pair<int, int>& p1, pair<int, int>& p2) {
        return p1.first < p2.first || (p1.first == p2.first && p1.second > p2.second);
    }
};

class Solution {
private:
    void mergeCount(vector<int>& indices, int first, int last, vector<int>& result, vector<int>& nums) {
        int count = last - first;
        if (count <= 1) {
            return;
        }
        
        int mid = first + count / 2;
        mergeCount(indices, first, mid, result, nums);
        mergeCount(indices, mid, last, result, nums);
        
        vector<int> temp;
        int idx1 = first;
        int idx2 = mid;
        int semicount = 0;
        while (idx1 < mid or idx2 < last) {
            if (idx2 == last or (idx1 < mid and nums[indices[idx1]] <= nums[indices[idx2]])) {
                temp.push_back(indices[idx1]);
                result[indices[idx1]] += semicount;
                idx1 += 1;
            }
            else {
                temp.push_back(indices[idx2]);
                semicount += 1;
                idx2 += 1;
            }
        }
        move(temp.begin(), temp.end(), indices.begin() + first);
    }
public:
    vector<int> countSmaller(vector<int> nums) {
        int n = nums.size();
        vector<int> indices(n, 0);
        vector<int> result(n, 0);
        
        iota(indices.begin(), indices.end(), 0);
        mergeCount(indices, 0, n, result, nums);
        return result;
    }
};

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
        LFUNode* prevNode = cur -> prev;
        LFUNode* nextNode = cur -> next;
        if (prevNode != nullptr) {
            prevNode -> next = nextNode;
        }
        if (nextNode != nullptr) {
            nextNode -> prev = prevNode;
        }
        if (minFreq == cur -> freq && freq2node[minFreq] -> next == freq2node[minFreq]) {
            freq2node.erase(minFreq);
            minFreq += 1;
        }
        
        cur -> freq += 1;
        if (freq2node.find(cur -> freq) == freq2node.end()) {
            LFUNode* newHead = new LFUNode(cur -> freq, -1, -1);
            newHead -> next = newHead;
            newHead -> prev = newHead;
            freq2node[cur -> freq] = newHead;
        }
        
        cur -> next = freq2node[cur -> freq] -> next;
        cur -> next -> prev = cur;
        freq2node[cur -> freq] -> next = cur;
        cur -> prev = freq2node[cur -> freq];
        
        return key2node[key] -> value;
    }
    
    void put(int key, int value) {
        if (key2node.find(key) != key2node.end()) {
            key2node[key] -> value = value;
            get(key);
            return;
        }
        
        if (key2node.size() == capacity) {
            LFUNode* listHead = freq2node[minFreq];
            LFUNode* last = listHead -> prev;
            listHead -> prev = last -> prev;
            last -> prev -> next = listHead;
            key2node.erase(last -> key);
            if (listHead -> next == listHead) {
                freq2node.erase(listHead -> freq);
            }
        }
        
        LFUNode* newNode = new LFUNode(1, key, value);
        minFreq = 1;
        key2node[key] = newNode;
        if (freq2node.find(minFreq) == freq2node.end()) {
            LFUNode* newHead = new LFUNode(minFreq, -1, -1);
            newHead -> next = newHead;
            newHead -> prev = newHead;
            freq2node[minFreq] = newHead;
        }
        newNode -> next = freq2node[minFreq] -> next;
        freq2node[minFreq] -> next -> prev = newNode;
        newNode -> prev = freq2node[minFreq];
        freq2node[minFreq] -> next = newNode;
    }
};

int main() {
    LFUCache lfu(2);
    lfu.put(1, 1);
    lfu.put(2, 2);
    lfu.get(1);
    lfu.put(3, 3);
    lfu.get(2);
    
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<int> vb({3,2});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({{1,2}, {0}, {0}});
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    
    s.countSmaller({2,9,10});
    return 0;
}
