/*
60. Permutation Sequence

The set [1,2,3,...,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for n = 3:

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
        vector<int> pos;
        int total = 1;
        for (int i = 1; i <= n; i++) {
            pos.push_back(i);
            total *= i;
        }
        
        string result = "";
        for (int i = 0; i != n; i++) {
            total = total / (n - i);
            int time = ((k - 1) / total) + 1;
            int digit;
            int j = 0;
            int x = 0;
            while (x < n) {
                if (pos.at(x) != 0) {
                    j++;
                    if (j == time) {
                        digit = pos.at(x);
                        pos.at(x) = 0;
                        x = n;
                    }
                }
                x++;
            }
            result += '0' + digit;
            k -= (time - 1) * total;
        }
        return result;
    }
};
