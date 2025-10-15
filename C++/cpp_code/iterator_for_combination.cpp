/*
5123. Iterator for Combination
https://leetcode.com/problems/iterator-for-combination/

Design an Iterator class, which has:
A constructor that takes a string characters of sorted distinct lowercase English letters
and a number combinationLength as arguments.

A function next()
that returns the next combination of length combinationLength in lexicographical order.

A function hasNext()
that returns True if and only if there exists a next combination.

Example:
CombinationIterator iterator = new CombinationIterator("abc", 2); // creates the iterator.
iterator.next(); // returns "ab"
iterator.hasNext(); // returns true
iterator.next(); // returns "ac"
iterator.hasNext(); // returns true
iterator.next(); // returns "bc"
iterator.hasNext(); // returns false

Constraints:
1 <= combinationLength <= characters.length <= 15
There will be at most 10^4 function calls per test.
It's guaranteed that all calls of the function next are valid.
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

class CombinationIterator {
private:
    queue<string> combinations;

    void dfs(string& curStr, int curIndex, string& characters, int len) {
        if (curStr.size() == len) {
            combinations.push(curStr);
            return;
        }

        for (int i = curIndex; characters.size() - i >= len - curStr.size(); ++i) {
            curStr.push_back(characters[i]);
            dfs(curStr, i + 1, characters, len);
            curStr.pop_back();
        }
    }
public:
    CombinationIterator(string characters, int combinationLength) {
        if (combinationLength > characters.size()) {
            return;
        }

        string curStr = "";
        dfs(curStr, 0, characters, combinationLength);
    }

    string next() {
        string result = combinations.front();
        combinations.pop();
        return result;
    }

    bool hasNext() {
        return !combinations.empty();
    }
};
/**
* Your CombinationIterator object will be instantiated and called as such:
* CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
* string param_1 = obj->next();
* bool param_2 = obj->hasNext();
*/
