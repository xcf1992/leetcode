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
    int calculate(string s) {
        int result = 0;
        int pos = 0;
        int n = s.size();
        while (pos < s.size()) {
            bool negative = false;
            while (pos < n && (s[pos] == '(' || s[pos] == ')')) {
                pos += 1;
            }
            
            if (pos < n && s[pos] == '-') {
                negative = true;
                pos += 1;
            }
            
            if (pos < n && s[pos] == '+') {
                pos += 1;
            }
            
            int temp = 0;
            while (pos < n && s[pos] >= '0' && s[pos] <= '9') {
                temp = temp * 10 + (s[pos] - '0');
                pos += 1;
            }
            
            if (negative) {
                temp = 0 - temp;
            }
            result += temp;
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v1({4,4});
    vector<int> v2({0,4});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{0,0,1,0,0}, {0,0,0,0,0}, {0,0,0,1,0}, {1,1,0,1,1}, {0,0,0,0,0}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(4,3));
    fuxk.push_back(make_pair(2,3));
    fuxk.push_back(make_pair(2,1));
    fuxk.push_back(make_pair(5,0));
    
    s.calculate("1+1");
}
