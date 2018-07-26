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

struct Tuple {
    int node;
    int bitMask;
    int cost;
    
    Tuple(int n, int b, int c) {
        node = n;
        bitMask = b;
        cost = c;
    }
};

struct TupleHash {
    size_t operator()(const Tuple& tuple) {
        return 97 * tuple.bitMask + 71 * tuple.node;
    }
};

struct TupleComp {
    bool operator()(const Tuple& a, const Tuple& b) {
        return a.node == b.node && a.bitMask == b.bitMask;
    }
};

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        
        unordered_set<Tuple, TupleHash, TupleComp> visited;
        queue<Tuple> bfs;
        for (int i = 0; i < n; i++) {
            int mask = (1 << i);
            visited.insert(Tuple(i, mask, 0));
            bfs.push(Tuple(i, mask, 0));
        }
        
        while (!bfs.empty()) {
            Tuple cur = bfs.front();
            bfs.pop();
            if (cur.bitMask == (1 << n) - 1) {
                return cur.cost;
            }
            
            for (int next : graph[cur.node]) {
                int mask = (cur.bitMask | 1 << next);
                Tuple tuple = Tuple(next, mask, cur.cost + 1);
                if (visited.find(tuple) == visited.end()) {
                    visited.insert(tuple);
                    bfs.push(tuple);
                }
            }
        }
        return -1;
    }
};

int main() {
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
    
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(0,1));
    fuxk.push_back(make_pair(0,2));
    //fuxk.push_back(make_pair(1,3));
    //fuxk.push_back(make_pair(0,4));
    //fuxk.push_back(make_pair(5,4));
    //fuxk.push_back(make_pair(6,4));
    //fuxk.push_back(make_pair(6,7));
    
    cout << s.shortestPathLength(matrix1) << endl;
    return 0;
}
