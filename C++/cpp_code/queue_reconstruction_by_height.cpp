/*
406. Queue Reconstruction by Height
https://leetcode.com/problems/queue-reconstruction-by-height/

Suppose you have a random list of people standing in a queue.
Each person is described by a pair of integers (h, k),
where h is the height of the person and k is the number of people in front of this person
who have a height greater than or equal to h.
Write an algorithm to reconstruct the queue.

Note:
The number of people is less than 1,100.

Example
Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
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
using namespace std;

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(),
             [](vector<int>& p1, vector<int>& p2) { return p1[0] > p2[0] or (p1[0] == p2[0] and p1[1] < p2[1]); });

        vector<vector<int>> result;
        for (int i = 0; i < people.size(); ++i) {
            result.insert(result.begin() + people[i][1], people[i]);
        }
        return result;
    }
};