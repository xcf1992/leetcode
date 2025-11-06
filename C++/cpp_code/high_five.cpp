/*
1086. High Five
Given a list of scores of different students,
return the average score of each student's top five scores in the order of each student's id.

Each entry items[i] has items[i][0] the student's id, and items[i][1] the student's score.
The average score is calculated using integer division.

Example 1:

Input: [[1,91],[1,92],[2,93],[2,97],[1,60],[2,77],[1,65],[1,87],[1,100],[2,100],[2,76]]
Output: [[1,87],[2,88]]
Explanation:
The average of the student with id = 1 is 87.
The average of the student with id = 2 is 88.6. But with integer division their average converts to 88.


Note:

1 <= items.length <= 1000
items[i].length == 2
The IDs of the students is between 1 to 1000
The score of the students is between 1 to 100
For each student, there are at least 5 scores
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<vector<int>> highFive(vector<vector<int>>& items) {
        map<int, vector<int>> count;
        for (vector<int>& item : items) {
            int id = item[0];
            int score = item[1];
            if (count.find(id) == count.end()) {
                count[id] = vector<int>(101, 0);
            }
            count[id][score] += 1;
        }

        vector<vector<int>> result;
        for (auto& it : count) {
            int id = it.first;
            vector<int> scores = it.second;
            int number = 0;
            int sum = 0;
            for (int i = 100; i >= 1 and number < 5; --i)
                if (scores[i] != 0) {
                    sum += i * min(5 - number, scores[i]);
                    number += min(5 - number, scores[i]);
                }
            result.push_back({id, sum / 5});
        }
        return result;
    }
};