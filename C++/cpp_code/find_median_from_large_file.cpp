/*
http://storypku.com/2017/10/leetcode-question-15-find-median-from-large-file-of-integers/
https://rextester.com/discussion/VSCU77544/Find-Median-in-Large-File-of-Integers
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
#include <numeric>
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