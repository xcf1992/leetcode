#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        if (nums.size() < 1) {
            return -1;
        }
        if (nums.size() == 1) {
            return 0;
        }

        int largest = nums[1] >= nums[0];
        int larger = nums[1] < nums[0];
        for (int i = 2; i < nums.size(); i++) {
            int num = nums[i];
            if (num > nums[largest]) {
                larger = largest;
                largest = i;
            } else if (num > nums[larger]) {
                larger = num;
            }
        }
        if (nums[larger] == 0) {
            return nums[largest] != 0 ? largest : -1;
        }
        return nums[largest] / nums[larger] >= 2 ? largest : -1;
    }
};