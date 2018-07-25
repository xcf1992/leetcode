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
    bool IsOpt(char ch) {
        return  ch == '+' ||ch == '-' ||ch == '*' ||ch == '/';
    }
    
    int Calc(int num1, int num2, char opt) {
        if (opt == '+') {
            return num1 + num2;
        }
        if (opt == '-') {
            return num1 - num2;
        }
        if (opt == '*') {
            return num1 * num2;
        }
        return num1 / num2;
    }
    
    void CalcTop(stack<int> &nums, stack<char> &opts) {
        int num2 = nums.top();
        nums.pop();
        
        int num1 = nums.top();
        nums.pop();
        
        char opt = opts.top();
        opts.pop();
        
        nums.push(Calc(num1, num2, opt));
    }
public:
    int calculate(string s) {
        stack<int> nums;
        stack<char> opts;
        int num = 0;
        for (int i = 0; i < s.size(); i++) {
            if (isdigit(s[i])) {
                num = num * 10 + s[i] - '0';
            }
            else if (IsOpt(s[i])) {
                nums.push(num);
                num = 0;
                if (s[i] == '+' || s[i] == '-') {
                    while (!opts.empty()) {
                        CalcTop(nums, opts);
                    }
                }
                else { // s[i] == '*' || s[i] == '/'
                    while (!opts.empty() && (opts.top() == '*'|| opts.top() == '/')) {
                        CalcTop(nums, opts);
                    }
                }
                opts.push(s[i]);
            }
            
        }
        nums.push(num);
        while (!opts.empty()) {
            CalcTop(nums, opts);
        }
        return nums.top();
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
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
    fuxk.push_back(make_pair(0,1));
    fuxk.push_back(make_pair(0,2));
    //fuxk.push_back(make_pair(1,3));
    //fuxk.push_back(make_pair(0,4));
    //fuxk.push_back(make_pair(5,4));
    //fuxk.push_back(make_pair(6,4));
    //fuxk.push_back(make_pair(6,7));
    
    cout << s.calculate("3 - 2 * 5") << endl;
    return 0;
}
