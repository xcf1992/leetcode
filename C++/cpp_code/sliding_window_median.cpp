/*
480. Sliding Window Median
Median is the middle value in an ordered integer list.
If the size of the list is even, there is no middle value.
So the median is the mean of the two middle value.

Examples:
[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right.
You can only see the k numbers in the window.
Each time the sliding window moves right by one position.
Your job is to output the median array for each window in the original array.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Median
---------------               -----
[1  3  -1] -3  5  3  6  7       1
1 [3  -1  -3] 5  3  6  7       -1
1  3 [-1  -3  5] 3  6  7       -1
1  3  -1 [-3  5  3] 6  7       3
1  3  -1  -3 [5  3  6] 7       5
1  3  -1  -3  5 [3  6  7]      6
Therefore, return the median sliding window as [1,-1,-1,3,5,6].

Note:
You may assume k is always valid, ie: k is always smaller than input array's size for non-empty array.
*/
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
/*
use multiset https://en.cppreference.com/w/cpp/container/multiset
std::multiset is an associative container that contains a sorted set of objects of type Key.
Unlike set, multiple keys with equivalent values are allowed.
Sorting is done using the key comparison function Compare.
Search, insertion, and removal operations have logarithmic complexity.

Everywhere the standard library uses the Compare requirements,
equivalence is determined by using the equivalence relation as described on Compare.
In imprecise terms, two objects a and b are considered equivalent if neither compares less than the other: !comp(a, b) and !comp(b, a).

The order of the elements that compare equivalent is the order of insertion and does not change. (since C++11)

std::multiset meets the requirements of Container, AllocatorAwareContainer, AssociativeContainer and ReversibleContainer.
*/
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
                result.push_back(k % 2 == 1 ? *low.rbegin() : ((double)(*low.rbegin()) + (double)(*high.begin())) / 2);
            }
        }
        return result;
    }
};

class Solution1 { // 24.03% the idea is basically keep window a sorted array, using insert to put new coming element at correct pos
private:
    // left is the number we are about to remove from window
    // right is the number is the number we are about to add into window
    void process(vector<int>& window, int left, int right) {
        auto it = lower_bound(window.begin(), window.end(), right);
        window.insert(it, right);
        it = lower_bound(window.begin(), window.end(), left);
        window.erase(it);
    }
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<int> window(nums.begin(), nums.begin() + k);
        sort(window.begin(), window.end());
        vector<double> result(nums.size() - k + 1);
        for (int i = 0; i < nums.size() - k + 1; i++) {
            result[i] = k % 2 == 0 ? (static_cast<double>(window[k / 2 - 1]) + (double)window[k / 2]) / 2 : window[k / 2];
            if (i + k < nums.size()) {
                process(window, nums[i], nums[i + k]);
            }
        }
        return result;
    }
};
