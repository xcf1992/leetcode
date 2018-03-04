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
    string removeDuplicateLetters(string s) {
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a'] += 1;
        }
        
        vector<bool> visited(26, false);
        string result = "";
        for (char c : s) {
            count[c - 'a'] -= 1;
            if (visited[c - 'a']) {
                continue;
            }
            
            if (!result.empty() && c < result.back() && count[result.back() - 'a'] > 0) {
                visited[result.back() - 'a'] = false;
                result.pop_back();
            }
            result.push_back(c);
            visited[c - 'a'] = true;
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({2,2,2,2,2});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{9,9,4},{6,7,8},{2,1,1}});
    
    s.removeDuplicateLetters("bcabc");
}
