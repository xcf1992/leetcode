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

int main() {
    Solution s;
    cout << s.lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext");
    return 0;
}