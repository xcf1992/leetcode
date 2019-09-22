/*
60. Permutation Sequence
https://leetcode.com/problems/permutation-sequence/

The set [1,2,3,...,n] contains a count of n! unique permutations.
By listing and labeling all of the permutations in order,
we get the following sequence for n = 3:
"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note:
Given n will be between 1 and 9 inclusive.
Given k will be between 1 and n! inclusive.

Example 1:
Input: n = 3, k = 3
Output: "213"

Example 2:
Input: n = 4, k = 9
Output: "2314"
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> digit;
        int count = 1;
        for (int i = 1; i <= n; i++) {
            digit.push_back(i);
            count *= i;
        }

        string result = "";
        for (int i = 0; i < n; i++) {
            count /= (n - i);
            int index = ((k - 1) / count) + 1;

            int available = 0;
            for (int pos = 0; pos < n; pos++) {
                if (digit[pos] == 0) {
                    continue;
                }

                available += 1;
                if (available < index) {
                    continue;
                }
                result.push_back('0' + digit[pos]);
                digit[pos] = 0;
                break;
            }
            k -= (index - 1) * count;
        }
        return result;
    }
};
