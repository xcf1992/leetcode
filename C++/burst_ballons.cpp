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
using namespace std;


class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1); nums.insert(nums.end(), 1);
        int size = nums.size();
        int result[size][size];
        memset(result, 0, sizeof(int) * size * size);

        for (int d = 2; d < size; d++) {
            for (int i = 0; i + d < size; i++) {
                int j = i + d;
                for (int k = i + 1; k < j; k++) {
                    result[i][j] = max(result[i][j], result[i][k] + nums[i] * nums[k] * nums[j] + result[k][j]);
                }
            }
        }

        return result[0][size - 1];
    }
};

int main() {
    Solution s;
    return 0;
}