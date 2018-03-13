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
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (nums.size() < 2 || k == 0) {
            return false;
        }
        set<long> windows;
        int left = 0;
        for (int i = 0; i < nums.size(); i++){
            if (i - left > k){
                windows.erase(nums[left]);
                left++;
            }
            set<long>::iterator it = windows.lower_bound((long)nums[i] - (long)t);
            if (it != windows.end()) {
                int x = *it;
                return true;
            }
            windows.insert(nums[i]);
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({4,2});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{1,2},{3},{3},{}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(0, 1));
    fuxk.push_back(make_pair(1, 2));
    fuxk.push_back(make_pair(3, 4));
    
    s.containsNearbyAlmostDuplicate(v2, 2, 1);
}
