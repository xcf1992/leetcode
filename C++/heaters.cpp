/*
 475. Heaters
 Winter is coming! Your first job during the contest is to design a standard heater with fixed warm radius to warm all the houses.

 Now, you are given positions of houses and heaters on a horizontal line, find out minimum radius of heaters so that all houses could be covered by those heaters.

 So, your input will be the positions of houses and heaters seperately, and your expected output will be the minimum radius standard of heaters.

 Note:
 Numbers of houses and heaters you are given are non-negative and will not exceed 25000.
 Positions of houses and heaters you are given are non-negative and will not exceed 10^9.
 As long as a house is in the heaters' warm radius range, it can be warmed.
 All the heaters follow your radius standard and the warm radius will the same.
 Example 1:
 Input: [1,2,3],[2]
 Output: 1
 Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
 Example 2:
 Input: [1,2,3,4],[1,4]
 Output: 1
 Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be warmed.
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
#include <set>
using namespace std;

class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(heaters.begin(), heaters.end());
        int result = INT_MIN;
        for (int house : houses) {
            int radius = INT_MAX;
            auto larger = lower_bound(heaters.begin(), heaters.end(), house);
            if (larger != heaters.end()) {
                radius = *larger - house;
            }
            if (larger != heaters.begin()) {
                radius = min(radius, house - *prev(larger));
            }
            result = max(result, radius);
        }
        return result;
    }
};

class Solution1 {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int result = INT_MIN;
        for (int house : houses) {
            int radius = INT_MAX;
            for (int heater : heaters) {
                radius = min(radius, abs(house - heater));
            }
            result = max(result, radius);
        }
        return result;
    }
};
