/*
 Given an array of integers A with even length, return true if and only if it is possible to reorder it such that A[2 * i + 1] = 2 * A[2 * i] for every 0 <= i < len(A) / 2.



 Example 1:

 Input: [3,1,3,6]
 Output: false
 Example 2:

 Input: [2,1,2,6]
 Output: false
 Example 3:

 Input: [4,-2,2,-4]
 Output: true
 Explanation: We can take two groups, [-2,-4] and [2,4] to form [-2,-4,2,4] or [2,4,-2,-4].
 Example 4:

 Input: [1,2,4,16,8,4]
 Output: false


 Note:

 0 <= A.length <= 30000
 A.length is even
 -100000 <= A[i] <= 100000
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
#include <numeric>
using namespace std;

class Solution {
public:
    bool canReorderDoubled(vector<int>& A) {
        map<int, int> count;
        for (int i = 0; i < A.size(); i++) {
            if (count.find(abs(A[i])) == count.end()) {
                count[abs(A[i])] = 1;
            }
            else {
                count[abs(A[i])] += 1;
            }
        }

        if (count[0] % 2 != 0) {
            return false;
        }
        count.erase(0);

        for (auto it = count.begin(); it != count.end(); it++) {
            int number = it -> first;
            if (count[number * 2] < count[number]) {
                return false;
            }
            count[2 * number] -= count[number];
            count[number] = 0;
        }

        for (auto it = count.begin(); it != count.end(); it++) {
            if (it -> second != 0) {
                return false;
            }
        }

        return true;
    }
};
