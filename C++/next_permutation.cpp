/*
31. Next Permutation
https://leetcode.com/problems/next-permutation/

Implement next permutation,
which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible,
it must rearrange it as the lowest possible order
(ie, sorted in ascending order).

The replacement must be in-place and use only constant extra memory.

Here are some examples.
Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
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
    void nextPermutation(vector<int> &num) {
        int n = num.size();
        if (n <= 1) {
            return;
        }

        int pos = n - 1;
        while (pos > 0 and num[pos - 1] >= num[pos]) {
            pos -= 1;
        }
        if (pos == 0) {
            reverse(num.begin(), num.end());
            return;
        }

        int end = n - 1;
        while (end >= pos and num[end] <= num[pos - 1]) {
            end -= 1;
        }
        swap(num[pos - 1], num[end]);
        reverse(num.begin() + pos, num.end());
    }
};
