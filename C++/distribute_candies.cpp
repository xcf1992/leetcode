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
    int distributeCandies(vector<int>& candies) {
        unordered_set<int> different_candy;

        for (int i = 0; i < candies.size(); i++) {
            different_candy.insert(candies[i]);
        }

        return min(candies.size() / 2, different_candy.size());
    }
};

int main() {
    Solution s;
    return 0;
}
