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
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        unordered_map<int, int> nextGreaterNum;
        stack<int> bigger;

        for (int num : nums) {
            nextGreaterNum[num] = -1;

            while (bingger.size() != 0 && num > bigger.top()) {
                nextGreaterNum[bigger.top()] = num;
                bigger.pop();
            }

            bigger.push(num);
        }

        vector<int> result;
        for (int num : findNums) {
            result.push_back(nextGreaterNum[num]);
        }

        return result;
    }
};


int main() {
    Solution s;
    return 0;
}