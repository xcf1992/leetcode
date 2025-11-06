/*
822. Card Flipping Game
On a table are N cards, with a positive integer printed on the front and back of each card (possibly different).

We flip any number of cards, and after we choose one card.

If the number X on the back of the chosen card is not on the front of any card,
then this number X is good.

What is the smallest number that is good?
If no number is good, output 0.

Here, fronts[i] and backs[i] represent the number on the front and back of card i.

A flip swaps the front and back numbers, so the value on the front is now on the back and vice versa.

Example:

Input: fronts = [1,2,4,4,7], backs = [1,3,4,1,3]
Output: 2
Explanation: If we flip the second card, the fronts are [1,3,4,4,7] and the backs are [1,2,4,1,3].
We choose the second card, which has number 2 on the back, and it isn't on the front of any card, so 2 is good.

Note:

1 <= fronts.length == backs.length <= 1000.
1 <= fronts[i] <= 2000.
1 <= backs[i] <= 2000.
*/
#include <iostream>
#include <sstream>
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

class Solution {
public:
    int flipgame(vector<int>& fronts, vector<int>& backs) {
        int n = fronts.size();
        unordered_set<int> bad;
        for (int i = 0; i < n; ++i) {
            if (fronts[i] == backs[i]) {
                bad.insert(fronts[i]);
            }
        }

        int result = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (bad.find(fronts[i]) == bad.end()) {
                result = min(result, fronts[i]);
            }
            if (bad.find(backs[i]) == bad.end()) {
                result = min(result, backs[i]);
            }
        }
        return result == INT_MAX ? 0 : result;
    }
};

class Solution1 {
private:
    bool canFlip(vector<int>& pos, vector<int>& fronts, vector<int>& backs) {
        for (int i : pos) {
            if (fronts[i] == backs[i]) {
                return false;
            }
        }
        return true;
    }

public:
    int flipgame(vector<int>& fronts, vector<int>& backs) {
        int n = fronts.size();
        unordered_map<int, vector<int>> front;
        unordered_map<int, vector<int>> back;
        for (int i = 0; i < n; i++) {
            front[fronts[i]].push_back(i);
            back[backs[i]].push_back(i);
        }

        int result = INT_MAX;
        for (int i = 0; i < n; i++) {
            int num = fronts[i];
            if (back.find(num) == back.end() or canFlip(back[num], fronts, backs)) {
                result = min(result, num);
            }

            num = backs[i];
            if (front.find(num) == front.end() or canFlip(front[num], backs, fronts)) {
                result = min(result, num);
            }
        }
        return result == INT_MAX ? 0 : result;
    }
};