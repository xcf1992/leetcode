/*
https://leetcode.com/problems/water-bottles-ii/description/
3100. Water Bottles II

You are given two integers numBottles and numExchange.

numBottles represents the number of full water bottles that you initially have. In one operation, you can perform one of
the following operations:

Drink any number of full water bottles turning them into empty bottles.
Exchange numExchange empty bottles with one full water bottle. Then, increase numExchange by one.
Note that you cannot exchange multiple batches of empty bottles for the same value of numExchange. For example, if
numBottles == 3 and numExchange == 1, you cannot exchange 3 empty water bottles for 3 full bottles.

Return the maximum number of water bottles you can drink.



Example 1:


Input: numBottles = 13, numExchange = 6
Output: 15
Explanation: The table above shows the number of full water bottles, empty water bottles, the value of numExchange, and
the number of bottles drunk. Example 2:


Input: numBottles = 10, numExchange = 3
Output: 13
Explanation: The table above shows the number of full water bottles, empty water bottles, the value of numExchange, and
the number of bottles drunk.


Constraints:

1 <= numBottles <= 100
1 <= numExchange <= 100
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
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int rst = numBottles;
        int empty_cnt = numBottles;
        int bottle_cnt = 0;
        while (empty_cnt >= numExchange) {
            empty_cnt -= numExchange;
            numExchange += 1;
            rst += 1;
            empty_cnt += 1;
        }
        return rst;
    }
};
