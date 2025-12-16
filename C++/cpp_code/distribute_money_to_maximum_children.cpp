/*
https://leetcode.com/problems/distribute-money-to-maximum-children/description/
2591. Distribute Money to Maximum Children

You are given an integer money denoting the amount of money (in dollars) that you have and another integer children
denoting the number of children that you must distribute the money to.

You have to distribute the money according to the following rules:

All money must be distributed.
Everyone must receive at least 1 dollar.
Nobody receives 4 dollars.
Return the maximum number of children who may receive exactly 8 dollars if you distribute the money according to the
aforementioned rules. If there is no way to distribute the money, return -1.



Example 1:

Input: money = 20, children = 3
Output: 1
Explanation:
The maximum number of children with 8 dollars will be 1. One of the ways to distribute the money is:
- 8 dollars to the first child.
- 9 dollars to the second child.
- 3 dollars to the third child.
It can be proven that no distribution exists such that number of children getting 8 dollars is greater than 1.
Example 2:

Input: money = 16, children = 2
Output: 2
Explanation: Each child can be given 8 dollars.


Constraints:

1 <= money <= 200
2 <= children <= 30
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
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    int distMoney(int money, int children) {
        if (money < children) {
            return -1;
        }

        if (money > children * 8) {
            return children - 1;
        }

        int rst = 0;
        while (money > 0 && money - 8 >= children - 1) {
            rst += 1;
            money -= 8;
            children -= 1;
        }

        if (money == 4 && children == 1) {
            rst -= 1;
        }
        return rst;
    }
};