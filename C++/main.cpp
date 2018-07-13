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
#include <set>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        if (n == 1) {
            return {0};
        }
        
        unordered_map<int, unordered_set<int>> graph;
        for (pair<int, int> edge : edges) {
            graph[edge.first].insert(edge.second);
            graph[edge.second].insert(edge.first);
        }
        
        vector<int> leaves;
        while (true) {
            for (int cur = 0; cur < n; cur++) {
                if (graph.find(cur) != graph.end() && graph[cur].size() <= 1) {
                    leaves.push_back(cur);
                }
            }
            
            if (leaves.size() <= 2) {
                break;
            }
            
            for (int leaf : leaves) {
                for (auto it = graph[leaf].begin(); it != graph[leaf].end(); it++) {
                    graph[*it].erase(graph[*it].find(leaf));
                }
                graph.erase(graph.find(leaf));
            }
        }
        return leaves;
    }
};

class KthLargest {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int K;
public:
    KthLargest(int k, vector<int> nums) {
        for (int num : nums) {
            minHeap.push(num);
        }
        K = k;
    }
    
    int add(int val) {
        minHeap.push(val);
        if (minHeap.size() > K) {
            minHeap.pop();
        }
        return minHeap.top();
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<int> vb({3,2});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({{0,0,1,1}, {1,0,1,0}, {1,1,0,0}});
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(0,1));
    fuxk.push_back(make_pair(0,2));
    //fuxk.push_back(make_pair(1,3));
    //fuxk.push_back(make_pair(0,4));
    //fuxk.push_back(make_pair(5,4));
    //fuxk.push_back(make_pair(6,4));
    //fuxk.push_back(make_pair(6,7));
    //s.findMinHeightTrees(3, fuxk);
    
    KthLargest kk(3, va);
    return 0;
}
