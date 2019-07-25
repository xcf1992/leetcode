/*
 403. Frog Jump
 A frog is crossing a river. The river is divided into x units and at each unit there may or may not exist a stone.
 The frog can jump on a stone, but it must not jump into the water.

 Given a list of stones' positions (in units) in sorted ascending order,
 determine if the frog is able to cross the river by landing on the last stone.
 Initially, the frog is on the first stone and assume the first jump must be 1 unit.

 If the frog's last jump was k units, then its next jump must be either k - 1, k, or k + 1 units.
 Note that the frog can only jump in the forward direction.

 Note:

 The number of stones is ≥ 2 and is < 1,100.
 Each stone's position will be a non-negative integer < 231.
 The first stone's position is always 0.
 Example 1:

 [0,1,3,5,6,8,12,17]

 There are a total of 8 stones.
 The first stone at the 0th unit, second stone at the 1st unit,
 third stone at the 3rd unit, and so on...
 The last stone at the 17th unit.

 Return true. The frog can jump to the last stone by jumping
 1 unit to the 2nd stone, then 2 units to the 3rd stone, then
 2 units to the 4th stone, then 3 units to the 6th stone,
 4 units to the 7th stone, and 5 units to the 8th stone.
 Example 2:

 [0,1,2,3,4,8,9,11]

 Return false. There is no way to jump to the last stone as
 the gap between the 5th and 6th stone is too large.
 */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
#include <numeric>
using namespace std;

class Solution { // dp
public:
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        unordered_map<int, unordered_set<int>> reach;
        reach[stones.front()].insert(0);
        for (int pos : stones) {
            for (int k : reach[pos]) {
                for (int step = max(1, k - 1); step <= k + 1; ++step) {
                    reach[pos + step].insert(step);
                }
            }
        }
        return reach[stones.back()].size() > 0;
    }
};

class Solution1 { // dfs with memo
private:
    bool check(int cur, int end, int lastJump, unordered_set<string>& visited, unordered_set<int>& stone) {
        if (cur == end) {
            return true;
        }

        if (stone.find(cur) == stone.end()) {
            return false;
        }

        string key = to_string(cur) + "_" + to_string(lastJump);
        if (visited.find(key) != visited.end()) {
            return false;
        }

        for (int i = lastJump - 1; i <= lastJump + 1; i++) {
            if (i > 0 and check(cur + i, end, i, visited, stone)) {
                return true;
            }
        }
        visited.insert(key);
        return false;
    }
public:
    bool canCross(vector<int>& stones) {
        unordered_set<int> s(stones.begin(), stones.end());
        unordered_set<string> visited;
        return check(stones.front(), stones.back(), 0, visited, s);
    }
};
