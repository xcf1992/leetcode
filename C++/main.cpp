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
    int longestSubstring(string s, int k) {
        unordered_map<char, int> letters;
        for (char c : s) {
            letters[c] += 1;
        }
        
        int result = 0;
        int start = -1;
        int end = 0;
        unordered_map<char, int> count;
        while (end < s.size()) {
            if (letters[s[end]] >= k) {
                count[s[end]] += 1;
            }
            else {
                bool isValid = true;
                for (auto letterNum : count) {
                    if (letterNum.second < k) {
                        isValid = false;
                    }
                    letters[letterNum.first] -= letterNum.second;
                }
                if (isValid) {
                    result = max(result, end - start - 1);
                }
                count.clear();
                start = end;
            }
            end += 1;
        }
        bool isValid = true;
        for (auto letterNum : count) {
            if (letterNum.second < k) {
                isValid = false;
            }
            letters[letterNum.first] -= letterNum.second;
        }
        if (isValid) {
            result = max(result, end - start - 1);
        }
        count.clear();
        return result;
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({7,2,5,10,8});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    cout << s.longestSubstring("bbaaacdb", 3) << endl;
    
}
