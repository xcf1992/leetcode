/*
1342. Reduce Array Size to The Half
https://leetcode.com/problems/reduce-array-size-to-the-half/

Given an array arr.
You can choose a set of integers and remove all the occurrences of these integers in the array.
Return the minimum size of the set so that at least half of the integers of the array are removed.

Example 1:
Input: arr = [3,3,3,3,5,5,5,2,2,7]
Output: 2
Explanation: Choosing {3,7} will make the new array [5,5,5,2,2] which has size 5 (i.e equal to half of the size of the old array).
Possible sets of size 2 are {3,5},{3,2},{5,2}.
Choosing set {2,7} is not possible as it will make the new array [3,3,3,3,5,5,5] which has size greater than half of the size of the old array.

Example 2:
Input: arr = [7,7,7,7,7,7]
Output: 1
Explanation: The only possible set you can choose is {7}. This will make the new array empty.

Example 3:
Input: arr = [1,9]
Output: 1

Example 4:
Input: arr = [1000,1000,3,7]
Output: 1

Example 5:
Input: arr = [1,2,3,4,5,6,7,8,9,10]
Output: 5

Constraints:
1 <= arr.length <= 10^5
arr.length is even.
1 <= arr[i] <= 10^5
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
#include "extra_data_types.hpp"
using namespace std;

struct myComp {
    bool operator()(pair<int, int>& a, pair<int, int>& b) {
        return a.second < b.second;
    }
};

class Solution {
public:
    int minSetSize(vector<int>& arr) {
        unordered_map<int, int> count;
        for (int num : arr) {
            count[num] += 1;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, myComp> pq;
        for (auto& c : count) {
            pq.push(c);
        }

        int result = 0;
        int curCount = 0;
        while (curCount < ceil(arr.size() / 2)) {
            curCount += pq.top().second;
            pq.pop();
            result += 1;
        }
        return result;
    }
};
