/*
341. Flatten Nested List Iterator
Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:

Input: [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false,
             the order of elements returned by next should be: [1,1,2,1,1].
Example 2:

Input: [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false,
             the order of elements returned by next should be: [1,4,6].

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
using namespace std;

// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class NestedIterator {
private:
    stack<vector<NestedInteger>::iterator> begins, ends;
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        begins.push(nestedList.begin());
        ends.push(nestedList.end());
    }

    int next() {
        hasNext();
        return (begins.top()++) -> getInteger();
    }

    bool hasNext() {
        while (begins.size()) {
            if (begins.top() == ends.top()) {
                begins.pop();
                ends.pop();
            } else {
                auto x = begins.top();
                if (x -> isInteger()) {
                    return true;
                }
                begins.top()++;
                begins.push(x -> getList().begin());
                ends.push(x -> getList().end());
            }
        }
        return false;
    }
};

class NestedIterator1 {
private:
    vector<int> nums;
    int pos = 0;

    void pushToList(vector<NestedInteger> &nestedList) {
        for (int i = 0; i < nestedList.size(); i++) {
            if (nestedList[i].isInteger()) {
                nums.push_back(nestedList[i].getInteger());
            }
            else {
                vector<NestedInteger> temp = nestedList[i].getList();
                pushToList(temp);
            }
        }
    }
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        pushToList(nestedList);
    }

    int next() {
        return nums[pos++];
    }

    bool hasNext() {
        return pos < nums.size();
    }
};

/**
 Your NestedIterator object will be instantiated and called as such:
 NestedIterator i(nestedList);
 while (i.hasNext()) cout << i.next();
 */

int main() {
    Solution s;
    return 0;
}