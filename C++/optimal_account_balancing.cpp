/*
465. Optimal Account Balancing

A group of friends went on holiday and sometimes lent each other money.
For example, Alice paid for Bill's lunch for $10. Then later Chris gave Alice $5 for a taxi ride.
We can model each transaction as a tuple (x, y, z) which means person x gave person y $z.
Assuming Alice, Bill, and Chris are person 0, 1, and 2 respectively (0, 1, 2 are the person's ID),
the transactions can be represented as [[0, 1, 10], [2, 0, 5]].

Given a list of transactions between a group of people,
return the minimum number of transactions required to settle the debt.

Note:
A transaction will be given as a tuple (x, y, z). Note that x ≠ y and z > 0.
Person's IDs may not be linear, e.g. we could have the persons 0, 1, 2 or we could also have the persons 0, 2, 6.

Example 1:
Input:
[[0,1,10], [2,0,5]]
Output:
2
Explanation:
Person #0 gave person #1 $10.
Person #2 gave person #0 $5.
Two transactions are needed. One way to settle the debt is person #1 pays person #0 and #2 $5 each.

Example 2:
Input:
[[0,1,10], [1,0,1], [1,2,5], [2,0,5]]
Output:
1
Explanation:
Person #0 gave person #1 $10.
Person #1 gave person #0 $1.
Person #1 gave person #2 $5.
Person #2 gave person #0 $5.
Therefore, person #1 only need to give person #0 $4, and all debt is settled.
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
private:
    int count(vector<int>& balance, int start) {
        while (start < balance.size() and balance[start] == 0) {
            start += 1;
        }

        if (start == balance.size()) {
            return 0;
        }

        int result = INT_MAX;
        for (int i = start + 1; i < balance.size(); ++i) {
            if (balance[start] * balance[i] < 0) {
                balance[i] += balance[start];
                result = min(result, 1 + count(balance, start + 1));
                balance[i] -= balance[start];
            }
        }
        return result;
    }
public:
    int minTransfers(vector<vector<int>>& transactions) {
        map<int, int> balance;
        for (vector<int>& transaction : transactions) {
            balance[transaction[0]] -= transaction[2];
            balance[transaction[1]] += transaction[2];
        }

        vector<int> nonZeroBalance;
        for (auto& it : balance) if (it.second != 0) {
            nonZeroBalance.push_back(it.second);
        }
        return count(nonZeroBalance, 0);
    }
};

// wrong answer [[1,5,8],[8,9,8],[2,3,9],[4,3,1]]
class Solution1 {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        map<int, int> balance;
        for (vector<int>& transaction : transactions) {
            balance[transaction[0]] -= transaction[2];
            balance[transaction[1]] += transaction[2];
        }

        int result = 0;
        for (auto it = balance.begin(); it != balance.end(); ++it) {
            if (it -> second != 0) {
                auto temp = it;
                for (auto jt = ++temp; jt != balance.end(); ++jt) {
                    if ((jt -> second > 0 and it -> second < 0) or (jt -> second < 0 and it -> second > 0)) {
                        result += 1;
                        if (abs(it -> second) > abs(jt -> second)) {
                            int op = (it -> second) / abs(it -> second);
                            it -> second = op * (abs(it -> second) - abs(jt -> second));

                            jt -> second = 0;
                        }
                        else {
                            int op = (jt -> second) / abs(jt -> second);
                            jt -> second = op * (abs(jt -> second) - abs(it -> second));

                            it -> second = 0;
                        }
                    }

                    if (it -> second == 0) {
                        break;
                    }
                }
            }
        }
        return result;
    }
};
