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
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        vector<pair<int, int>> result;

        auto comp = [](const pair<int, int>& p1, const pair<int, int>& p2) { 
            return p1.first > p2.first || (p1.first == p2.first && p1.second < p2.second); 
        };

        sort(people.begin(), people.end(), comp);
        for (auto& p : people) {
            result.insert(result.begin() + p.second, p);
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}