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
    int find(vector<int> nums, int k, int left, int right) {
        if (left >= right) {
            return left;
        }

        int guess = left + (right - left) / 2;
        int count = 0;
        int median = left;
        for (int num : nums) {
            if (num <= guess) {
                count += 1;
                median = max(median, num);
            }
        }

        if (count == k) {
            return median;
        }
        if (count < k) {
            return find(nums, k, median + 1, right);
        }
        return find(nums, k, left, median);
    }
public:
    double findMedian(vector<int> nums) {
        int len = 0;
        int minVal = INT_MAX;
        int maxVal = INT_MIN;
        for (int num : nums) {
            len += 1;
            minVal = min(minVal, num);
            maxVal = max(maxVal, num);
        }

        if (len % 2 != 0) {
            return find(nums, len / 2 + 1, minVal, maxVal);
        }
        double sum = find(nums, len / 2, minVal, maxVal) + find(nums, len / 2 + 1, minVal, maxVal);
        return sum / 2.0;
    }
};

int main() {
    vector<int> temp1({1,2,3,5,6,6,6,6,6,8});
    Solution s;
    cout << s.findMedian(temp1);

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
}
