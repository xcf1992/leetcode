/*
388. Longest Absolute File Path

Suppose we abstract our file system by a string in the following manner:

The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:

dir
    subdir1
    subdir2
        file.ext
The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2 containing a file file.ext.

The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" represents:

dir
    subdir1
        file1.ext
        subsubdir1
    subdir2
        subsubdir2
            file2.ext
The directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file file1.ext and an empty second-level sub-directory subsubdir1. subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.

We are interested in finding the longest (number of characters) absolute path to a file within our file system. For example, in the second example above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", and its length is 32 (not including the double quotes).

Given a string representing the file system in the above format, return the length of the longest absolute path to file in the abstracted file system. If there is no file in the system, return 0.

Note:
The name of a file contains at least a . and an extension.
The name of a directory or sub-directory will not contain a ..
Time complexity required: O(n) where n is the size of the input string.

Notice that a/aa/aaa/file1.txt is not the longest file path, if there is another path aaaaaaaaaaaaaaaaaaaaa/sth.png.


*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;

class Solution {
public:
    int lengthLongestPath(string input) {
        vector<int> path;
        int maxLen = 0;
        int level = 0;
        int start = 0;
        bool isFile = false;

        for (int i = 0; i < input.size(); i++) {
            while (i < input.size() && input[i] != '\n') {
                if (input[i] == '.') {
                    isFile = true;
                }
                i++;
            }
            i += 1;

            int len = i - start - 1;
            if (isFile) { // if it is a file
                if (path.empty()) {
                    maxLen = len;
                }
                else if (level >= path.size()) {
                    maxLen = max(maxLen, path.back() + 1 + len);
                }
                else {
                    while (path.size() > level) {
                        path.pop_back();
                    }
                    if (path.empty()) {
                        maxLen = max(maxLen, len);
                    }
                    else {
                        maxLen = max(maxLen, path.back() + 1 + len);
                    }
                }
                isFile = false;
            }
            else { // if it is a folder
                while (path.size() > level) {
                    path.pop_back();
                }
                if (path.empty()) {
                    path.push_back(len);
                }
                else {
                    path.push_back(len + 1 + path.back());
                }
            }

            level = 0;
            while (i < input.size() && input[i] == '\t') {
                level += 1;
                i += 1;
            }
            start = i;
            i -= 1;
        }

        return maxLen;
    }
};
