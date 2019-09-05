/*
 Given an unsorted array of integers, find the number of longest increasing subsequence.

 Example 1:
 Input: [1,3,5,4,7]
 Output: 2
 Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].
 Example 2:
 Input: [2,2,2,2,2]
 Output: 5
 Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1, so output 5.
 Note: Length of the given array will be not exceed 2000 and the answer is guaranteed to be fit in 32-bit signed int.
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

class Solution1 {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) {
            return 0;
        }

        int result = 1;
        int curLength = 1;
        vector<int> length(n, 1);
        vector<int> count(n, 1);

        for (int i = 1; i < n; i++) {
            length[i] = 1;
            count[i] = 1;
            if (curLength == 1) {
                result += 1;
            }

            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    if (length[j] + 1 == length[i]) {
                        count[i] += count[j];
                        if (length[i] == curLength) {
                            result += count[j];
                        }
                    }
                    else if (length[j] + 1 > length[i]) {
                        length[i] = length[j] + 1;
                        count[i] = count[j];
                        if (length[i] > curLength) {
                            curLength = length[i];
                            result = count[i];
                        }
                        else if (length[i] == curLength) {
                            result += count[i];
                        }
                    }
                }
            }
        }

        return result;
    }
};

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) {
            return 0;
        }

        int curLength = 1;
        vector<int> length(n, 1);
        vector<int> count(n, 1);

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    if (length[j] + 1 == length[i]) {
                        count[i] += count[j];
                    }
                    else if (length[j] + 1 > length[i]) {
                        length[i] = length[j] + 1;
                        count[i] = count[j];
                    }
                }
            }
            curLength = max(curLength, length[i]);
        }

        int result = 0;
        for (int i = 0; i < n; i++) {
            result += length[i] == curLength ? count[i] : 0;
        }
        return result;
    }
};
