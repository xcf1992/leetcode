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
    int maxDistance(vector<vector<int>>& arrays) {
        int minVal = INT_MAX;
        int maxVal = INT_MIN;
        int i = 0;
        for (; i < arrays.size(); i++) {
            if (!arrays[i].empty()) {
                minVal = arrays[i].front();
                maxVal = arrays[i].back();
                break;
            }
        }
        
        int result = INT_MIN;
        for (int j = i + 1; j < arrays.size(); j++) {
            if (!arrays[j].empty()) {
                int newMin = arrays[i].front();
                int newMax = arrays[i].back();
                
                result = max(result, max(newMax - minVal, maxVal - newMin));
                minVal = min(newMin, minVal);
                maxVal = max(newMax, maxVal);
            }
        }
        return result;
    }
};
int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v1({1,0,0,0,0,1});
    vector<int> v2({0,4});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{1,2,3}, {4,5}, {1,2,3}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(4,3));
    fuxk.push_back(make_pair(2,3));
    fuxk.push_back(make_pair(2,1));
    fuxk.push_back(make_pair(5,0));
    
    s.maxDistance(matrix);
}
