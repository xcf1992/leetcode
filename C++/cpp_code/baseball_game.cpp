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
using namespace std;

/*
 * Given a list of strings, each string can be one of the 4 following types:
 *    Integer (one round's score): Directly represents the number of points you get in this round.
 *    "+" (one round's score): Represents that the points you get in this round are the sum of the last two valid round's points.
 *    "D" (one round's score): Represents that the points you get in this round are the doubled data of the last valid round's points.
 *    "C" (an operation, which isn't a round's score): Represents the last valid round's points you get were invalid and should be removed.
 * Each round's operation is permanent and could have an impact on the round before and the round after.
 * You need to return the sum of the points you could get in all the rounds.
*/
class Solution {
public:
    int calPoints(vector<string>& ops) {
        vector<int> points;
        for (string op : ops) {
            if (op == "C") {
                points.pop_back();
            }
            else if (op == "D") {
                points.push_back(points.back() * 2);
            }
            else if (op == "+") {
                int n = points.size();
                points.push_back(points[n - 1] + points[n - 2]);
            }Ø
            else {
                points.push_back(stoi(op));
            }
        }

        int sum = 0;
        for (int i : points) {
            sum += i;
        }
        return sum;
    }
};