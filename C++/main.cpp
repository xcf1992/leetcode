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
using namespace std;

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> result;
        multiset<int> low, high;
        for (int i = 0; i < nums.size(); ++i) {
            if (i >= k) {
                if (nums[i - k] <= *low.rbegin()) {
                    low.erase(low.find(nums[i - k]));
                }
                else {
                    high.erase(high.find(nums[i - k]));
                }
            }

            // the newly insert element could be very big and may should belong to high part
            low.insert(nums[i]);
            high.insert(*low.rbegin());
            low.erase(prev(low.end()));
            if (low.size() < high.size()) { // these steps may seem duplicate, but it is actually to make sure low.size() is at least equal to high
                low.insert(*high.begin());
                high.erase(high.begin());
            }

            if (i >= k - 1) {
                result.push_back(k % 2 == 1 ? *low.rbegin() : ((double)(*low.rbegin()) + (double)(*high.begin()) / 2));
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,3,2,4});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<char>> matrix({
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    });
    vector<string> words({"cat","cats","and","sand","dog"});
    s.medianSlidingWindow(temp, 4);
}
