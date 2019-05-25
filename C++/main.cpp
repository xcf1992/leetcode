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
#include <numeric>
using namespace std;

class Solution {
private:
    int n;
    int getNext(vector<int>& nums, int i) {
        int next = i + nums[i];
        while (next < 0) {
            next += n;
        }
        return next % n;
    }
public:
    bool circularArrayLoop(vector<int>& nums) {
        n = nums.size();
        if (n < 2) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            if (i == getNext(nums, i)) {
                nums[i] = 0;
            }
        }
        
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                continue;
            }
            int slow = i;
            int fast = i;
            bool moveForward = nums[slow] > 0;
            bool wrong = false;
            do {
                slow = getNext(nums, slow);
                fast = getNext(nums, getNext(nums, fast));
                if ((moveForward && nums[slow] < 0) || (!moveForward && nums[slow] > 0)) {
                    wrong = true;
                }
            } while (nums[slow] != 0 && slow != fast && !wrong);
            
            if (nums[slow] != 0 && slow == fast && !wrong) {
                return true;
            }
            nums[i] = 0;
        }
        return false;
    }
};

int main() {
    int x = stoi("001");
    Solution s;
    vector<int> temp({1,1,1,1,1,1,1,1,1,-5});
    vector<vector<int>> matrix({
        {1,2,3,4,5},
        {6,7,8,9,10},
        {11,12,13,14,15},
        {16,17,18,19,20},
        {21,22,23,24,25}
    });
    s.circularArrayLoop(temp);
}
