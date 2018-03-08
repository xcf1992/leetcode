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
    int threeSumSmaller(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int left = 0;
        int right = nums.size() - 1;
        int result = 0;
        while (left < right - 1) {
            for (int mid = left + 1; mid < right; mid++) {
                if (nums[left] + nums[mid] + nums[right] < target) {
                    result += 1;
                }
                else {
                    break;
                }
            }
            if (nums[left] + nums[left + 1] + nums[right] >= target) {
                right -= 1;
            }
            else {
                left += 1;
                while (left < right - 1 && nums[left] == nums[left - 1]) {
                    left += 1;
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({3,1,0,-2});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{0,1},{1,2},{3,4}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(0, 1));
    fuxk.push_back(make_pair(1, 2));
    fuxk.push_back(make_pair(3, 4));
    
    s.threeSumSmaller(v2, 4);
}
