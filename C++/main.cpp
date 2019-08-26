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
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

struct TrieNode {
    unordered_map<string, TrieNode*> child;
    bool isFile;
    int content;

    TrieNode() {
        isFile = false;
        content = -1;
    }
};

class FileSystem {
private:
    TrieNode* root = nullptr;

    vector<string> split(string& path) {
        vector<string> result;
        string cur = "";
        for (int i = 1; i < path.size(); ++i) {
            char c = path[i];
            if (c == '/') {
                result.push_back(path);
                path = "";
            }
            else {
                path.push_back(c);
            }
        }
        result.push_back(cur);
        return result;
    }

    bool insert(vector<string>& path, int value) {
        int n = path.size();
        TrieNode* cur = root;
        for (int i = 0; i < n; ++i) {
            if (cur -> child.find(path[i]) == cur -> child.end() and i != n - 1) {
                return false;
            }
            else {
                cur -> child[path[i]] = new TrieNode();
            }
            cur = cur -> child[path[i]];
        }
        cur -> isFile = true;
        cur -> content = value;
        return true;
    }

    int find(vector<string>& path) {
        int n = path.size();
        TrieNode* cur = root;
        for (int i = 0; i < n; ++i) {
            if (cur -> child.find(path[i]) == cur -> child.end()) {
                return -1;
            }
            cur = cur -> child[path[i]];
        }
        return cur -> content;
    }
public:
    FileSystem() {
        root = new TrieNode();
    }

    bool create(string path, int value) {
        vector<string> p = split(path);
        return insert(p, value);
    }

    int get(string path) {
        vector<string> p = split(path);
        return find(p);
    }
};

int main() {
    FileSystem fs;
    fs.create("/a", 1);
    fs.get("/a");

    vector<int> temp({1,1,2,2,1,1});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1},
        {1,2},
        {2,1},
        {1,0},
        {0,2},
        {0,0},
        {1,1}
    });
    vector<vector<int>> matrix2({
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
    });
    vector<string> words({"hot","dot","dog","lot","log","cog"});
    TreeNode* r1 = new TreeNode(0);
    TreeNode* r2 = new TreeNode(1);
    TreeNode* r3 = new TreeNode(3);
    r1 -> left = r2;
}
