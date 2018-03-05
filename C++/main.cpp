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
private:
    bool isValid(string num1, string num2, string num3) {
        if (num1.size() > 0 && num1[0] == '0') {
            return false;
        }
        if (num2.size() > 0 && num2[0] == '0') {
            return false;
        }
        
        string sum = add(num1, num2);
        if (sum == num3) {
            return true;
        }
        
        if (num3.size() <= sum.size() || sum != num3.substr(0, sum.size())) {
            return false;
        }
        return isValid(num2, sum, num3.substr(sum.size()));
    }
    
    string add(string num1, string num2) {
        return to_string(stol(num1) + stol(num2));
    }
public:
    bool isAdditiveNumber(string num) {
        int n = num.size();
        for (int i = 1; i <= n / 2; i++) {
            for (int j = 1; j <= (n - i) / 2; j++) {
                if (isValid(num.substr(0, i), num.substr(i, j), num.substr(i + j))) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({2,2,2,2,2});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{9,9,4},{6,7,8},{2,1,1}});
    
    s.isAdditiveNumber("101");
}
