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
    int thirdMax(vector<int>& nums) {
        long biggest = (long)INT_MIN - 1;
        long bigger = INT_MIN - 1;
        long big = INT_MIN - 1;
        for (long num : nums) {
            if (num > biggest) {
                big = bigger;
                bigger = biggest;
                biggest = num;
            }
            else if (num != biggest && num > bigger) {
                big = bigger;
                bigger = num;
            }
            else if (num != biggest && num != bigger && num > big) {
                big = num;
            }
        }
        return big == INT_MIN - 1 ? biggest : big;
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v1({1,2,-2147483648});
    vector<int> v2({0,4});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{0,0,1,0,0}, {0,0,0,0,0}, {0,0,0,1,0}, {1,1,0,1,1}, {0,0,0,0,0}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(4,3));
    fuxk.push_back(make_pair(2,3));
    fuxk.push_back(make_pair(2,1));
    fuxk.push_back(make_pair(5,0));
    
    s.thirdMax(v1);
}
