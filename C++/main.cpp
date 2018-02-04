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
    int compress(string chars) {
        if (chars.empty()) {
            return 0;
        }
        int start = 0;
        int end = 0;
        int count = 0;
        while (end < chars.size()) {
            if (chars[end] == chars[start]) {
                count++;
                end++;
            }
            else {
                start += 1;
                if (count > 1) {
                    string num = to_string(count);
                    for (char c : num) {
                        chars[start] = c;
                        start += 1;
                    }
                }
                count = 1;
                chars[start] = chars[end];
                end++;
            }
        }
        start += 1;
        if (count > 1) {
            string num = to_string(count);
            for (char c : num) {
                chars[start] = c;
                start += 1;
            }
        }
        return start;
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({7,2,5,10,8});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    cout << s.compress("abcccc") << endl;
    
}
