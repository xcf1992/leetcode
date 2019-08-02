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
#include <numeric>
#include "extra_data_types.hpp"
using namespace std;

class Solution {
private:
    bool parse(string& expression, int& pos) {
        int n = expression.size();
        if (pos >= n) {
            return true;
        }

        char op = ' ';
        vector<bool> vals;
        while (pos < n and expression[pos] != ')') {
            if (expression[pos] == '!' or expression[pos] == '&' or expression[pos] == '|') {
                if (op == ' ') {
                    op = expression[pos];
                }
                else {
                    vals.push_back(parse(expression, pos));
                }
            }
            else if (expression[pos] == 't' or expression[pos] == 'f') {
                vals.push_back('t' == expression[pos]);
            }
            pos += 1;
        }
        pos += 1; // skip the last )

        if (op == '!') {
            return !vals[0];
        }
        while (vals.size() > 1) {
            bool v1 = vals.back();
            vals.pop_back();
            bool v2 = vals.back();
            vals.pop_back();
            if (op == '&') {
                vals.push_back(v1 and v2);
            }
            else {
                vals.push_back(v1 or v2);
            }
        }
        return vals[0];
    }
public:
    bool parseBoolExpr(string expression) {
        int pos = 0;
        cout << expression.size();
        return parse(expression, pos);
    }
};

int main() {
    Solution s;
    vector<int> temp({1,17,8});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1},
        {1,2},
        {2,1},
        {1,0},
        {0,2},
        {0,0},
        {1,1}
    });
    vector<vector<int>> matrix2({
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
    });
    vector<string> words({"hot","dot","dog","lot","log","cog"});
    TreeNode* r1 = new TreeNode(0);
    TreeNode* r2 = new TreeNode(1);
    TreeNode* r3 = new TreeNode(3);
    r1 -> left = r2;
    s.parseBoolExpr("!(&(&(!(&(f)),&(t),|(f,f,t)),&(t),&(t,t,f)))");
}
