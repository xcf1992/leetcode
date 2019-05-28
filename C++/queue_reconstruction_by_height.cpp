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
        sort(people.begin(), people.end(), [](vector<int>& p1, vector<int>& p2) {
            return p1[0] > p2[0] || (p1[0] == p2[0] && p1[1] < p2[1]); 
        });

        vector<vector<int>> result;
        for (int i = 0; i < people.size(); ++i) {
            if (people[i][1] == result.size()) {
                result.push_back(people[i]);
            }
            else {
                result.insert(result.begin() + people[i][1], people[i]);
            }
        }
        return result;
    }
};
