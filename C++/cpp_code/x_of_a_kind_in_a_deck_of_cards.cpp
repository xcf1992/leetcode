/*
914. X of a Kind in a Deck of Cards

In a deck of cards, each card has an integer written on it.
Return true if and only if you can choose X >= 2
such that it is possible to split the entire deck into 1 or more groups of cards, where:

Each group has exactly X cards.
All the cards in each group have the same integer.

Example 1:
Input: [1,2,3,4,4,3,2,1]
Output: true
Explanation: Possible partition [1,1],[2,2],[3,3],[4,4]

Example 2:
Input: [1,1,1,2,2,2,3,3]
Output: false
Explanation: No possible partition.

Example 3:
Input: [1]
Output: false
Explanation: No possible partition.

Example 4:
Input: [1,1]
Output: true
Explanation: Possible partition [1,1]

Example 5:
Input: [1,1,2,2,2,2]
Output: true
Explanation: Possible partition [1,1],[2,2],[2,2]

Note:
1 <= deck.length <= 10000
0 <= deck[i] < 10000
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

// all cards have common divisor equal to or bigger than 2
class Solution {
private:
    int gcd(int n1, int n2) {
        if (n1 < n2) {
            swap(n1, n2);
        }
        return n2 == 0 ? n1 : gcd(n2, n1 % n2);
    }

public:
    bool hasGroupsSizeX(vector<int> &deck) {
        unordered_map<int, int> count;
        for (int card: deck) {
            count[card] += 1;
        }

        int result = 0;
        for (auto &it: count) {
            result = gcd(it.second, result);
        }
        return result >= 2;
    }
};