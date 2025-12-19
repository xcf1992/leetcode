/*
https://leetcode.com/problems/count-square-sum-triples/description/
1925. Count Square Sum Triples

A square triple (a,b,c) is a triple where a, b, and c are integers and a2 + b2 = c2.

Given an integer n, return the number of square triples such that 1 <= a, b, c <= n.



Example 1:

Input: n = 5
Output: 2
Explanation: The square triples are (3,4,5) and (4,3,5).
Example 2:

Input: n = 10
Output: 4
Explanation: The square triples are (3,4,5), (4,3,5), (6,8,10), and (8,6,10).


Constraints:

1 <= n <= 250
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <set>

using namespace std;

class Solution {
public:
    int countTriples(int n) {
        int res = 0;
        // enumerate a and b
        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                // determine if it meets the requirements
                int c = int(sqrt(a * a + b * b + 1.0));
                if (c <= n && c * c == a * a + b * b) {
                    ++res;
                }
            }
        }
        return res;
    }
};