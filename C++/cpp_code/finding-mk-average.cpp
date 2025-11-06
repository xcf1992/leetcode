/*
1825. Finding MK Average
https://leetcode.com/problems/finding-mk-average/

You are given two integers, m and k, and a stream of integers.
You are tasked to implement a data structure that calculates the MKAverage for the stream.

The MKAverage can be calculated using these steps:

If the number of the elements in the stream is less than m you should consider the MKAverage to be -1.
Otherwise, copy the last m elements of the stream to a separate container.
Remove the smallest k elements and the largest k elements from the container.
Calculate the average value for the rest of the elements rounded down to the nearest integer.
Implement the MKAverage class:
MKAverage(int m, int k) Initializes the MKAverage object with an empty stream and the two integers m and k.
void addElement(int num) Inserts a new element num into the stream.
int calculateMKAverage() Calculates and returns the MKAverage for the current stream rounded down to the nearest
integer.

Example 1:
Input
["MKAverage", "addElement", "addElement", "calculateMKAverage", "addElement", "calculateMKAverage", "addElement",
"addElement", "addElement", "calculateMKAverage"]
[[3, 1], [3], [1], [], [10], [], [5], [5], [5], []]
Output
[null, null, null, -1, null, 3, null, null, null, 5]
Explanation
MKAverage obj = new MKAverage(3, 1);
obj.addElement(3);        // current elements are [3]
obj.addElement(1);        // current elements are [3,1]
obj.calculateMKAverage(); // return -1, because m = 3 and only 2 elements exist.
obj.addElement(10);       // current elements are [3,1,10]
obj.calculateMKAverage(); // The last 3 elements are [3,1,10].
                          // After removing smallest and largest 1 element the container will be [3].
                          // The average of [3] equals 3/1 = 3, return 3
obj.addElement(5);        // current elements are [3,1,10,5]
obj.addElement(5);        // current elements are [3,1,10,5,5]
obj.addElement(5);        // current elements are [3,1,10,5,5,5]
obj.calculateMKAverage(); // The last 3 elements are [5,5,5].
                          // After removing smallest and largest 1 element the container will be [5].
                          // The average of [5] equals 5/1 = 5, return 5


Constraints:
3 <= m <= 105
1 <= k*2 < m
1 <= num <= 105
At most 105 calls will be made to addElement and calculateMKAverage.
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
#include <numeric>
using namespace std;
/*
A bit lengthy; the idea is to keep track of the left, mid, and right sets.
When removing or adding numbers, we reballance these sets so that the size of left and right stays k.

Also, we keep track of sum for elements in mid. That way, the calculate function is O(1).

Finally, to track the current m numbers, we use a circular array of size m.
*/
class MKAverage {
public:
    int m = 0, k = 0, sz = 0, pos = 0;
    long sum = 0;
    vector<int> v;
    multiset<int> left, mid, right;

    void remove(int n) {
        if (n <= *rbegin(left))
            left.erase(left.find(n));
        else if (n <= *rbegin(mid)) {
            auto it = mid.find(n);
            sum -= *it;
            mid.erase(it);
        } else
            right.erase(right.find(n));
        if (left.size() < k) {
            left.insert(*begin(mid));
            sum -= *begin(mid);
            mid.erase(begin(mid));
        }
        if (mid.size() < sz) {
            mid.insert(*begin(right));
            sum += *begin(right);
            right.erase(begin(right));
        }
    }

    void add(int n) {
        left.insert(n);
        if (left.size() > k) {
            auto it = prev(end(left));
            mid.insert(*it);
            sum += *it;
            left.erase(it);
        }
        if (mid.size() > sz) {
            auto it = prev(end(mid));
            sum -= *it;
            right.insert(*it);
            mid.erase(it);
        }
    }

    MKAverage(int m, int k) : m(m), k(k), sz(m - 2 * k) {
        v = vector<int>(m);
    }

    void addElement(int num) {
        if (pos >= m)
            remove(v[pos % m]);
        add(num);
        v[pos++ % m] = num;
    }

    int calculateMKAverage() {
        if (pos < m)
            return -1;
        return sum / sz;
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */