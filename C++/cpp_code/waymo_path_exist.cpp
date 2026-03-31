/*
check if path exist in a graph, without visiting the same nodes twice
B - A
|   |
C - D
 \ /
  E
path: "CBADE", true
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <climits>
#include <map>
#include <cassert>
using namespace std;

struct Node {
    char c;
    vector<Node*> children;

    Node(char c_) {
        c = c_;
    }
};

class Solution {
private:
    void find_start(Node* cur, vector<Node*>& start_nodes, unordered_set<Node*>& visited, char tgt_c) {
        if (cur == nullptr) {
            return;
        }

        if (visited.find(cur) != visited.end()) {
            return;
        }

        visited.insert(cur);
        if (cur->c == tgt_c) {
            start_nodes.push_back(cur);
        }

        for (Node* child : cur->children) {
            find_start(child, start_nodes, visited, tgt_c);
        }
    }

    bool check(Node* cur, string& path, size_t idx, unordered_set<Node*>& visited) {
        if (cur == nullptr) {
            return false;
        }

        if (idx >= path.size()) {
            return true;
        }

        if (visited.find(cur) != visited.end()) {
            return false;
        }

        if (path[idx] != cur->c) {
            return false;
        }

        visited.insert(cur);
        for (Node* child : cur->children) {
            if (check(child, path, idx + 1, visited)) {
                return true;
            }
        }
        visited.erase(cur);
        return false;
    }
public:
    bool path_exist(Node* root, string& path) {
        if (root == nullptr) {
            return false;
        }

        if (path.empty()) {
            return false;
        }

        vector<Node*> start_nodes;
        unordered_set<Node*> visited;
        find_start(root, start_nodes, visited, path[0]);

        for (Node* start : start_nodes) {
            visited.clear();
            if (check(start, path, 0, visited)) {
                return true;
            }
        }
        return false;
    }
};
