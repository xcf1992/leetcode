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


class NumArray {
private:
    vector<int> sum;
public:
    NumArray(vector<int> &nums) {
        sum.push_back(0);
        for (auto i : nums) {
            sum.push_back(sum.back() + i);
        }
    }

    int sumRange(int i, int j) {
        return sum[j + 1] - sum[i];
    }
};


// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);

int main() {
    Solution s;
    return 0;
}