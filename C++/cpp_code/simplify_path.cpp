/*
71. Simplify Path
https://leetcode.com/problems/encode-and-decode-strings/

Given an absolute path for a file (Unix-style), simplify it.
Or in other words, convert it to the canonical path.

In a UNIX-style file system, a period . refers to the current directory.
Furthermore, a double period .. moves the directory up a level.
For more information, see: Absolute path vs relative path in Linux/Unix

Note that the returned canonical path must always begin with a slash /,
and there must be only a single slash / between two directory names.
The last directory name (if it exists) must not end with a trailing /.
Also, the canonical path must be the shortest string representing the absolute path.

Example 1:
Input: "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.

Example 2:
Input: "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.

Example 3:
Input: "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.

Example 4:
Input: "/a/./b/../../c/"
Output: "/c"

Example 5:
Input: "/a/../../b/../c//.//"
Output: "/c"

Example 6:
Input: "/a//b////c/d//././/.."
Output: "/a/b/c"
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

class Solution {
public:
    string simplifyPath(string path) {
        if (path.size() <= 1) {
            return path;
        }

        path += '/';
        vector<string> dirs;
        string cur = "";
        for (int i = 0; i != path.size(); i++) {
            if (path[i] == '/') {
                if (!cur.empty()) {
                    if (cur == "..") {
                        if (!dirs.empty()) {
                            dirs.pop_back();
                        }
                    } else if (cur != ".") {
                        dirs.push_back(cur);
                    }
                    cur = "";
                }
            } else {
                cur.push_back(path[i]);
            }
        }

        string result = "/";
        for (int i = 0; i != dirs.size(); i++) {
            result += dirs[i];
            if (i != dirs.size() - 1) {
                result += "/";
            }
        }
        return result;
    }
};