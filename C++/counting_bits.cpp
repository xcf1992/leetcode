/*
338. Counting Bits

Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.

Example 1:

Input: 2
Output: [0,1,1]
Example 2:

Input: 5
Output: [0,1,1,2,1,2]
Follow up:

It is very easy to come up with a solution with run time O(n*sizeof(integer)). But can you do it in linear time O(n) /possibly in a single pass?
Space complexity should be O(n).
Can you do it like a boss? Do it without using any builtin function like __builtin_popcount in c++ or in any other language.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> result;
        result.push_back(0);
        for (int i = 1; i <= num; i++) {
            result.push_back(result[i >> 1] + (i & 1));
        }
        return result;
    }
};

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> result(num + 1, 0);
        for (int i = 1; i <= num; i++) {
            int quotient = i >> 1;
            if (i & 1) {
                result[i] = result[quotient] + 1;
            }
            else {
                result[i] = result[quotient];
            }
        }
        return result;
    }
};
