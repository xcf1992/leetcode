/*
765. Couples Holding Hands
N couples sit in 2N seats arranged in a row and want to hold hands. We want to know the minimum number of swaps so that every couple is sitting side by side. A swap consists of choosing any two people, then they stand up and switch seats.

The people and seats are represented by an integer from 0 to 2N-1, the couples are numbered in order, the first couple being (0, 1), the second couple being (2, 3), and so on with the last couple being (2N-2, 2N-1).

The couples' initial seating is given by row[i] being the value of the person who is initially sitting in the i-th seat.

Example 1:

Input: row = [0, 2, 1, 3]
Output: 1
Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
Example 2:

Input: row = [3, 2, 0, 1]
Output: 0
Explanation: All couples are already seated side by side.
Note:

len(row) is even and in the range of [4, 60].
row is guaranteed to be a permutation of 0...len(row)-1.
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
#include <map>
#include <numeric>
using namespace std;

/*
https://leetcode.com/problems/couples-holding-hands/discuss/336706/The-general-mathematical-idea%3A-permutation-graph-and-graph-decomposition.
*/
class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int n = row.size();
        vector<int> pos(n , 0);
        for (int i = 0; i < n; i++) {
            pos[row[i]] = i;
        }

        int result = 0;
        for (int i = 0; i < n; i += 2) {
            int odd = row[i] % 2 == 0 ? 1 : -1;
            if (row[i] + odd != row[i + 1]) {
                int couple = pos[row[i] + odd];
                swap(pos[row[i] + odd], pos[row[i + 1]]);
                swap(row[couple], row[i + 1]);
                result += 1;
            }
        }
        return result;
    }
};

/*
union-find
hint:
Say there are N two-seat couches.
For each couple, draw an edge from the couch of one partner to the couch of the other partner.

so all the connected couches will become separate components,
the sum of number of couches in each component minus 1 will be the number of swaps needed.
*/
class Solution1 {
private:
    int find(vector<int>& parent, int num) {
        if (parent[num] != num) {
            parent[num] = find(parent, parent[num]);
        }
        return parent[num];
    }
public:
    int minSwapsCouples(vector<int>& row) {
        int n = row.size();
        vector<int> couch(n, 0);
        for (int i = 0; i < n; ++i) {
            couch[row[i]] = i / 2;
        }

        vector<int> count(n / 2, 1);
        vector<int> parent(n / 2, 1);
        iota(parent.begin(), parent.end(), 0);
        for (int i = 0; i < n - 1; i += 2) {
            int p1 = find(parent, couch[i]);
            int p2 = find(parent, couch[i + 1]);
            if (p1 != p2) {
                parent[p1] = p2;
                count[p2] += count[p1];
            }
        }

        int components = 0;
        for (int i = 0; i < n / 2; ++i) {
            if (parent[i] == i) {
                components += 1;
            }
        }
        return n / 2 - components;
    }
};
