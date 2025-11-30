/*
588. Design In-Memory File System
https://leetcode.com/problems/design-in-memory-file-system/

Design an in-memory file system to simulate the following functions:
ls: Given a path in string format.
If it is a file path, return a list that only contains this file's name.
If it is a directory path, return the list of file and directory names in this directory.
Your output (file and directory names together) should in lexicographic order.

mkdir: Given a directory path that does not exist,
you should make a new directory according to the path.
If the middle directories in the path don't exist either,
you should create them as well. This function has void return type.

addContentToFile: Given a file path and file content in string format.
If the file doesn't exist, you need to create that file containing given content.
If the file already exists, you need to append given content to original content.
This function has void return type.

readContentFromFile: Given a file path, return its content in string format.

Example:
Input:
["FileSystem","ls","mkdir","addContentToFile","ls","readContentFromFile"]
[[],["/"],["/a/b/c"],["/a/b/c/d","hello"],["/"],["/a/b/c/d"]]
Output:
[null,[],null,null,["a"],"hello"]
Explanation:
filesystem

Note:
You can assume all file or directory paths are absolute paths which begin with / and do not end with / except that the
path is just "/". You can assume that all operations will be passed valid parameters and users will not attempt to
retrieve file content or list a directory or file that does not exist. You can assume that all directory names and file
names only contain lower-case letters, and same names won't exist in the same directory.
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
#include <map>
#include <numeric>
using namespace std;

struct TrieNode {
    bool isFile = false;
    string content = "";
    map<string, TrieNode*> children;
};

class FileSystem {
private:
    TrieNode* root;

    vector<string> splitString(string path) {
        path = path.substr(1);
        vector<string> result;
        for (size_t pos = 0; (pos = path.find('/')) != string::npos; path = path.substr(pos + 1)) {
            result.push_back(path.substr(0, pos));
        }
        if (path != "") {
            result.push_back(path);
        }
        return result;
    }

public:
    FileSystem() {
        root = new TrieNode();
    }

    vector<string> ls(string path) {
        vector<string> paths = splitString(path);

        TrieNode* cur = root;
        for (string& p : paths) {
            cur = cur->children[p];
        }

        if (cur->isFile) {
            return {paths.back()};
        }

        vector<string> result;
        for (auto& p : cur->children) {
            result.push_back(p.first);
        }
        return result;
    }

    void mkdir(string path) {
        vector<string> paths = splitString(path);
        TrieNode* cur = root;
        for (string& p : paths) {
            if (cur->children[p] == nullptr) {
                cur->children[p] = new TrieNode();
            }
            cur = cur->children[p];
        }
    }

    void addContentToFile(string filePath, string content) {
        vector<string> paths = splitString(filePath);
        TrieNode* cur = root;
        for (string& p : paths) {
            if (cur->children[p] == nullptr) {
                cur->children[p] = new TrieNode();
            }
            cur = cur->children[p];
        }
        cur->isFile = true;
        cur->content += content;
    }

    string readContentFromFile(string filePath) {
        vector<string> paths = splitString(filePath);
        TrieNode* cur = root;
        for (string& p : paths) {
            cur = cur->children[p];
        }
        return cur->content;
    }
};

/*
Your FileSystem object will be instantiated and called as such:
FileSystem* obj = new FileSystem();
vector<string> param_1 = obj->ls(path);
obj->mkdir(path);
obj->addContentToFile(filePath,content);
string param_4 = obj->readContentFromFile(filePath);
*/