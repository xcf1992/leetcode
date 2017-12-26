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
    vector<string> findRelativeRanks(vector<int>& nums) {
        unordered_map<int, int> places;
        priority_queue<int> rank;
        for (int i = 0; i < nums.size(); i++) {
            places[nums[i]] = i;
            rank.push(nums[i]);
        }

        vector<string> result(nums.size(), "");
        int count = 1;
        while (rank.size() > 0) {
            if (count == 1) {
                result[places[rank.top()]] = "Gold Medal";
            }
            else if (count == 2) {
                result[places[rank.top()]] = "Silver Medal";
            }
            else if (count == 3) {
                result[places[rank.top()]] = "Bronze Medal";
            }
            else {
                result[places[rank.top()]] = to_string(count);
            }
            rank.pop();
            count += 1;
        }
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}
