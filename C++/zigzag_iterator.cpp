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

/*
Given two 1d vectors, implement an iterator to return their elements alternately.

For example, given two 1d vectors:

v1 = [1, 2]
v2 = [3, 4, 5, 6]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1, 3, 2, 4, 5, 6].

Follow up: What if you are given k 1d vectors? How well can your code be extended to such cases?

Clarification for the follow up question - Update (2015-09-18):
The "Zigzag" order is not clearly defined and is ambiguous for k > 2 cases. If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic". For example, given the following input:

[1,2,3]
[4,5,6,7]
[8,9]
It should return [1,4,8,2,5,9,3,6,7].
*/

class ZigzagIterator {
private:
    queue<pair<vector<int>::iterator, vector<int>::iterator>> zigZag;
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if (!v1.empty()) {
            zigZag.push(make_pair(v1.begin(), v1.end()));
        }
        if (!v2.empty()) {
            zigZag.push(make_pair(v2.begin(), v2.end()));
        }
    }

    int next() {
        auto it = zigZag.front().first;
        auto endIt = zigZag.front().second;
        zigZag.pop();
        if (it + 1 != endIt) {
            zigZag.push(make_pair(it + 1, endIt));
        }
        return *it;
    }

    bool hasNext() {
        return !zigZag.empty();
    }
};