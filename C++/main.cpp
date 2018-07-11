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
private:
    bool check(string s, int pos, int left, int right) {
        if (pos == s.size()) {
            return right == left;
        }
        
        if (s[pos] == '(') {
            return check(s, pos + 1, left + 1, right);
        }
        if (s[pos] == ')') {
            if (right == left) {
                return false;
            }
            return check(s, pos + 1, left, right + 1);
        }
        if (right == left) {
            return check(s, pos + 1, left + 1, right) || check(s, pos + 1, left, right);
        }
        return check(s, pos + 1, left + 1, right) || check(s, pos + 1, left, right + 1) || check(s, pos + 1, left, right);
    }
public:
    bool checkValidString(string s) {
        return check(s, 0, 0, 0);
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({6,8});
    vector<int> vb({3,2});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({{0,0,1,1}, {1,0,1,0}, {1,1,0,0}});
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(4,3));
    fuxk.push_back(make_pair(2,3));
    fuxk.push_back(make_pair(2,1));
    fuxk.push_back(make_pair(5,0));
    
    int a = 1;
    int b = 2;
    b += a = 3;
    return 0;
}
