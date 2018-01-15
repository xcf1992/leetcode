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

class Solution {
public:
    int findMin(vector<int>& nums) {
        int start = 0;
        int end = nums.size() - 1;
        while (start < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] > nums[start]) {
                start = mid + 1;
            }
            else if (nums[mid] < nums[end]) {
                end = mid;
            }
        }
        return nums[start];
    }
};


int main() {
    Solution s;
    vector<int> v{3,4,5,1,2};
    s.findMin(v);
}
