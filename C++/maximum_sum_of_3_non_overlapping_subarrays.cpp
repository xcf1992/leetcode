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
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int maxSum = 0;
        vector<int> sum = {0}, posLeft(n, 0), posRight(n, n - k), result(3, 0);

        for (int i : nums) {
            sum.push_back(sum.back() + i);
        }

        int temp = sum[k] - sum[0];
        for (int i = k; i < n; i++) {
            if (sum[i + 1] - sum[i + 1 - k] > temp) {
                posLeft[i] = i - k + 1;
                temp = sum[i + 1] - sum[i + 1 - k];
            }
            else {
                posLeft[i] = posLeft[i - 1];
            }
        }

        temp = sum[n] - sum[n - k];
        for (int i = n - k - 1; i >= 0; i--) {
            if (sum[i + k] - sum[i] > temp) {
                posRight[i] = i;
                temp = sum[i + k] - sum[i];
            }
            else {
                posRight[i] = posRight[i + 1];
            }
        }

        for (int i = k; i <= n - 2 * k; i++) {
            int left = posLeft[i - 1];
            int right = posRight[i + k];
            temp = sum[left + k] - sum[left] +
                   sum[i + k] - sum[i] +
                   sum[right + k] - sum[right];
            if (temp > maxSum) {
                maxSum = temp;
                result = {left, i, right};
            }
        }

        return result;
    }
};