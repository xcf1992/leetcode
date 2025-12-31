/*
https://leetcode.com/problems/delete-duplicate-folders-in-system/description/
1948. Delete Duplicate Folders in System

Due to a bug, there are many duplicate folders in a file system. You are given a 2D array paths, where paths[i] is an
array representing an absolute path to the ith folder in the file system.

For example, ["one", "two", "three"] represents the path "/one/two/three".
Two folders (not necessarily on the same level) are identical if they contain the same non-empty set of identical
subfolders and underlying subfolder structure. The folders do not need to be at the root level to be identical. If two
or more folders are identical, then mark the folders as well as all their subfolders.

For example, folders "/a" and "/b" in the file structure below are identical. They (as well as their subfolders) should
all be marked: /a /a/x /a/x/y /a/z /b /b/x /b/x/y /b/z However, if the file structure also included the path "/b/w",
then the folders "/a" and "/b" would not be identical. Note that "/a/x" and "/b/x" would still be considered identical
even with the added folder. Once all the identical folders and their subfolders have been marked, the file system will
delete all of them. The file system only runs the deletion once, so any folders that become identical after the initial
deletion are not deleted.

Return the 2D array ans containing the paths of the remaining folders after deleting all the marked folders. The paths
may be returned in any order.



Example 1:


Input: paths = [["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]]
Output: [["d"],["d","a"]]
Explanation: The file structure is as shown.
Folders "/a" and "/c" (and their subfolders) are marked for deletion because they both contain an empty
folder named "b".
Example 2:


Input: paths = [["a"],["c"],["a","b"],["c","b"],["a","b","x"],["a","b","x","y"],["w"],["w","y"]]
Output: [["c"],["c","b"],["a"],["a","b"]]
Explanation: The file structure is as shown.
Folders "/a/b/x" and "/w" (and their subfolders) are marked for deletion because they both contain an empty folder named
"y". Note that folders "/a" and "/c" are identical after the deletion, but they are not deleted because they were not
marked beforehand. Example 3:


Input: paths = [["a","b"],["c","d"],["c"],["a"]]
Output: [["c"],["c","d"],["a"],["a","b"]]
Explanation: All folders are unique in the file system.
Note that the returned array can be in a different order as the order does not matter.


Constraints:

1 <= paths.length <= 2 * 104
1 <= paths[i].length <= 500
1 <= paths[i][j].length <= 10
1 <= sum(paths[i][j].length) <= 2 * 105
path[i][j] consists of lowercase English letters.
No two paths lead to the same folder.
For any folder not at the root level, its parent folder will also be in the input.
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

using namespace std;

struct Node {
    string name;
    unordered_map<string, Node*> children;
    string signature;

    Node(string name) : name(name) {
    }
};

class Solution {
private:
    void get_signature(Node* node, unordered_map<string, int>& signature_cnt) {
        if (node->children.empty()) {
            node->signature = "";
            return;
        }

        vector<string> child_signatures;
        for (const auto& [name, child] : node->children) {
            get_signature(child, signature_cnt);
            child_signatures.push_back(name + "(" + child->signature + ")");
        }
        sort(child_signatures.begin(), child_signatures.end());

        node->signature = "";
        for (const string& sig : child_signatures) {
            node->signature += sig;
        }
        signature_cnt[node->signature]++;
    }

    void get_remain(Node* node, vector<string>& cur_path, vector<vector<string>>& result,
              unordered_map<string, int>& signature_cnt) {
        if (!node->children.empty() && signature_cnt[node->signature] >= 2) {
            return;
        }

        cur_path.push_back(node->name);
        result.push_back(cur_path);
        for (const auto& [name, child] : node->children) {
            get_remain(child, cur_path, result, signature_cnt);
        }
        cur_path.pop_back();
    }
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        Node* root = new Node("");
        for (const auto& path : paths) {
            Node* curr = root;
            for (const string& folder : path) {
                if (curr->children.find(folder) == curr->children.end()) {
                    curr->children[folder] = new Node(folder);
                }
                curr = curr->children[folder];
            }
        }

        unordered_map<string, int> signature_cnt;
        get_signature(root, signature_cnt);

        vector<vector<string>> rst;
        vector<string> cur_path;
        for (const auto& [name, child] : root->children) {
            get_remain(child, cur_path, rst, signature_cnt);
        }

        delete root;
        return rst;
    }
};
