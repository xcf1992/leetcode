/*
1166. Design File System
https://leetcode.com/problems/design-file-system/

You are asked to design a file system which provides two functions:
create(path, value):
Creates a new path and associates a value to it if possible and returns True.
Returns False if the path already exists or its parent path doesn't exist.

get(path):
Returns the value associated with a path or returns -1 if the path doesn't exist.

The format of a path is one or more concatenated strings of the form:
/ followed by one or more lowercase English letters.

For example, /leetcode and /leetcode/problems are valid paths while an empty string and / are not.
Implement the two functions.
Please refer to the examples for clarifications.

Example 1:

Input:
["FileSystem","create","get"]
[[],["/a",1],["/a"]]
Output:
[null,true,1]
Explanation:
FileSystem fileSystem = new FileSystem();

fileSystem.create("/a", 1); // return true
fileSystem.get("/a"); // return 1
Example 2:

Input:
["FileSystem","create","create","get","create","get"]
[[],["/leet",1],["/leet/code",2],["/leet/code"],["/c/d",1],["/c"]]
Output:
[null,true,true,2,false,-1]
Explanation:
FileSystem fileSystem = new FileSystem();

fileSystem.create("/leet", 1); // return true
fileSystem.create("/leet/code", 2); // return true
fileSystem.get("/leet/code"); // return 2
fileSystem.create("/c/d", 1); // return false because the parent path "/c" doesn't exist.
fileSystem.get("/c"); // return -1 because this path doesn't exist.

Constraints:
The number of calls to the two functions is less than or equal to 10^4 in total.
2 <= path.length <= 100
1 <= value <= 10^9
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
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
            if (path[i] == '/') {
                result.push_back(cur);
                cur = "";
            } else {
                cur.push_back(path[i]);
            }
        }
        result.push_back(cur);
        return result;
    }

    bool insert(vector<string>& path, int value) {
        int n = path.size();
        TrieNode* cur = root;
        for (int i = 0; i < n; ++i) {
            if (cur->child.find(path[i]) == cur->child.end()) {
                if (i != n - 1) {
                    return false;
                }
                cur->child[path[i]] = new TrieNode();
            } else {
                if (i == n - 1) {
                    return false;  // the path already exist
                }
            }
            cur = cur->child[path[i]];
        }
        cur->isFile = true;
        cur->content = value;
        return true;
    }

    int find(vector<string>& path) {
        int n = path.size();
        TrieNode* cur = root;
        for (int i = 0; i < n; ++i) {
            if (cur->child.find(path[i]) == cur->child.end()) {
                return -1;
            }
            cur = cur->child[path[i]];
        }
        return cur->content;
    }

public:
    FileSystem() {
        root = new TrieNode();
    }

    bool createPath(string path, int value) {
        vector<string> p = split(path);
        return insert(p, value);
    }

    int get(string path) {
        vector<string> p = split(path);
        return find(p);
    }
};

/*
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * bool param_1 = obj->create(path,value);
 * int param_2 = obj->get(path);
 */