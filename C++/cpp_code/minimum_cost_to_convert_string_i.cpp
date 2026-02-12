/*
https://leetcode.com/problems/minimum-cost-to-convert-string-i/description/
2976. Minimum Cost to Convert String I

You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English letters. You
are also given two 0-indexed character arrays original and changed, and an integer array cost, where cost[i] represents
the cost of changing the character original[i] to the character changed[i].

You start with the string source. In one operation, you can pick a character x from the string and change it to the
character y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y.

Return the minimum cost to convert the string source to the string target using any number of operations. If it is
impossible to convert source to target, return -1.

Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].



Example 1:

Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost
= [2,5,5,1,2,20] Output: 28 Explanation: To convert the string "abcd" to string "acbe":
- Change value at index 1 from 'b' to 'c' at a cost of 5.
- Change value at index 2 from 'c' to 'e' at a cost of 1.
- Change value at index 2 from 'e' to 'b' at a cost of 2.
- Change value at index 3 from 'd' to 'e' at a cost of 20.
The total cost incurred is 5 + 1 + 2 + 20 = 28.
It can be shown that this is the minimum possible cost.
Example 2:

Input: source = "aaaa", target = "bbbb", original = ["a","c"], changed = ["c","b"], cost = [1,2]
Output: 12
Explanation: To change the character 'a' to 'b' change the character 'a' to 'c' at a cost of 1, followed by changing the
character 'c' to 'b' at a cost of 2, for a total cost of 1 + 2 = 3. To change all occurrences of 'a' to 'b', a total
cost of 3 * 4 = 12 is incurred. Example 3:

Input: source = "abcd", target = "abce", original = ["a"], changed = ["e"], cost = [10000]
Output: -1
Explanation: It is impossible to convert source to target because the value at index 3 cannot be changed from 'd' to
'e'.


Constraints:

1 <= source.length == target.length <= 105
source, target consist of lowercase English letters.
1 <= cost.length == original.length == changed.length <= 2000
original[i], changed[i] are lowercase English letters.
1 <= cost[i] <= 106
original[i] != changed[i]
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
#include <climits>

using namespace std;

class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed,
                          vector<int>& cost) {
        vector<vector<long long>> min_cost(26, vector<long long>(26, LONG_LONG_MAX));
        for (int i = 0; i < 26; i++) {
            min_cost[i][i] = 0;
        }

        for (int i = 0; i < original.size(); i++) {
            int u = original[i] - 'a';
            int v = changed[i] - 'a';
            min_cost[u][v] = min(min_cost[u][v], (long long)cost[i]);
        }

        /*
         * it is floy warshall algorithm;
         * and the key is to put k at very outer loop;
         * the order of k values does not matter, it can be random actually
         * it means we want to find the shortest dist between i, j, through k now
         * and we already know the shortest pass between i, j, though any value before k, could utilize multiple values before k
         * in the end we will know the shortest between i, j, through any number of values, which will be the min
         * At step k:
         * You already solved:
         * best i → k using {0..k-1}
         * best k → j using {0..k-1}
         * min_cost[i][k] + min_cost[k][j]
         * you’re actually testing:
         * EVERY path that reaches k and leaves k using earlier nodes.
         */
        for (int k = 0; k < 26; k++) {
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < 26; j++) {
                    if (min_cost[i][k] == LONG_LONG_MAX || min_cost[k][j] == LONG_LONG_MAX) {
                        continue;
                    }

                    min_cost[i][j] = min(min_cost[i][j], min_cost[i][k] + min_cost[k][j]);
                }
            }
        }

        long long rst = 0;
        for (int i = 0; i < source.size(); i++) {
            int u = source[i] - 'a';
            int v = target[i] - 'a';
            if (u == v) {
                continue;
            }
            if (min_cost[u][v] == LONG_LONG_MAX) {
                return -1;
            }
            rst += min_cost[u][v];
        }
        return rst;
    }
};
