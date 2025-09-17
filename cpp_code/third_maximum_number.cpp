/*
 414. Third Maximum Number
 Given a non-empty array of integers,
 return the third maximum number in this array.
 If it does not exist, return the maximum number.
 The time complexity must be in O(n).

 Example 1:
 Input: [3, 2, 1]

 Output: 1

 Explanation: The third maximum is 1.
 Example 2:
 Input: [1, 2]

 Output: 2

 Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
 Example 3:
 Input: [2, 2, 3, 1]

 Output: 1

 Explanation: Note that the third maximum here means the third maximum distinct number.
 Both numbers with value 2 are both considered as second maximum.
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
#include <set>
using namespace std;

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long biggest = (long)INT_MIN - 1;
        long bigger = (long)INT_MIN - 1;
        long big = (long)INT_MIN - 1;
        for (long num : nums) {
            if (num > biggest) {
                big = bigger;
                bigger = biggest;
                biggest = num;
            }
            else if (num != biggest and num > bigger) {
                big = bigger;
                bigger = num;
            }
            else if (num != biggest and num != bigger and num > big) {
                big = num;
            }
        }
        return big == (long)INT_MIN - 1 ? biggest : big;
    }
};
