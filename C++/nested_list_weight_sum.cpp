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


/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
private:
    int calculate(vector<NestedInteger>& nestedList, int depth) {
        int result = 0;
        for (int i = 0; i < nestedList.size(); i++) {
            if (nestedList[i].isInteger()) {
                result += nestedList[i].getInteger() * depth;
            }
            else {
                result += calculate(nestedList[i].getList(), depth + 1);
            }
        }
        return result;
    }

public:
    int depthSum(vector<NestedInteger>& nestedList) {
        return calculate(nestedList, 1);
    }
};

int main() {
    Solution s;
    return 0;
}