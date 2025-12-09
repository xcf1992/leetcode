/*
https://leetcode.com/problems/finding-pairs-with-a-certain-sum/description/
1865. Finding Pairs With a Certain Sum

You are given two integer arrays nums1 and nums2. You are tasked to implement a data structure that supports queries of
two types:

Add a positive integer to an element of a given index in the array nums2.
Count the number of pairs (i, j) such that nums1[i] + nums2[j] equals a given value (0 <= i < nums1.length and 0 <= j <
nums2.length). Implement the FindSumPairs class:

FindSumPairs(int[] nums1, int[] nums2) Initializes the FindSumPairs object with two integer arrays nums1 and nums2.
void add(int index, int val) Adds val to nums2[index], i.e., apply nums2[index] += val.
int count(int tot) Returns the number of pairs (i, j) such that nums1[i] + nums2[j] == tot.


Example 1:

Input
["FindSumPairs", "count", "add", "count", "count", "add", "add", "count"]
[[[1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]], [7], [3, 2], [8], [4], [0, 1], [1, 1], [7]]
Output
[null, 8, null, 2, 1, null, null, 11]

Explanation
FindSumPairs findSumPairs = new FindSumPairs([1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]);
findSumPairs.count(7);  // return 8; pairs (2,2), (3,2), (4,2), (2,4), (3,4), (4,4) make 2 + 5 and pairs (5,1), (5,5)
make 3 + 4 findSumPairs.add(3, 2); // now nums2 = [1,4,5,4,5,4] findSumPairs.count(8);  // return 2; pairs (5,2), (5,4)
make 3 + 5 findSumPairs.count(4);  // return 1; pair (5,0) makes 3 + 1 findSumPairs.add(0, 1); // now nums2 =
[2,4,5,4,5,4] findSumPairs.add(1, 1); // now nums2 = [2,5,5,4,5,4] findSumPairs.count(7);  // return 11; pairs (2,1),
(2,2), (2,4), (3,1), (3,2), (3,4), (4,1), (4,2), (4,4) make 2 + 5 and pairs (5,3), (5,5) make 3 + 4


Constraints:

1 <= nums1.length <= 1000
1 <= nums2.length <= 105
1 <= nums1[i] <= 109
1 <= nums2[i] <= 105
0 <= index < nums2.length
1 <= val <= 105
1 <= tot <= 109
At most 1000 calls are made to add and count each.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class FindSumPairs {
private:
    vector<int> nums1_;
    vector<int> nums2_;
    unordered_map<int, int> freq2_;
    int max_val2_;

public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) : nums1_(nums1), nums2_(nums2) {
        max_val2_ = INT_MIN;
        sort(nums1_.begin(), nums1_.end());
        for (const int& num : nums2_) {
            freq2_[num] += 1;
            max_val2_=max(max_val2_, num);
        }
    }

    void add(int index, int val) {
        int origin_val = nums2_[index];
        freq2_[origin_val] -= 1;
        if (freq2_[origin_val] == 0) {
            freq2_.erase(origin_val);
        }

        int new_val = origin_val + val;
        nums2_[index] = new_val;
        freq2_[new_val] += 1;
        if (new_val > max_val2_) {
            max_val2_ = new_val;
        }
    }

    int count(int tot) {
        int rst = 0;
        int idx = lower_bound(nums1_.begin(), nums1_.end(), tot - max_val2_) - nums1_.begin();
        for (int i = idx; i < nums1_.size(); i++) {
            if (nums1_[i] >= tot) {
                break;
            }

            if (freq2_.find(tot - nums1_[i]) != freq2_.end()) {
                rst += freq2_[tot - nums1_[i]];
            }
        }
        return rst;
    }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */