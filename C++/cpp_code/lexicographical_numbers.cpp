/*
386. Lexicographical Numbers
https://leetcode.com/problems/lexicographical-numbers/

Given an integer n, return 1 - n in lexicographical order.
For example, given 13, return: [1,10,11,12,13,2,3,4,5,6,7,8,9].

Please optimize your algorithm to use less time and space.
The input size may be as large as 5,000,000.
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
/*
imagine the process like a preorder traversal of the tree
    1                                           2
 10          11 12 13                        20          21 22 23...
100 101                                  200 201
......
cur * 10 will be moving to the left child,
cur + 1 will be moving to the right sibling.
*/
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> result(n);
        int current = 1;
        for (int i = 0; i < n; i++) {
            result[i] = current;
            if (current * 10 <= n) {
                current *= 10;
            }
            else {
                if (current == n) {
                    current /= 10;
                }
                current += 1;
                while (current % 10 == 0) {
                    current /= 10;
                }
            }
        }
        return result;
    }
};
