#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
#include <set>
#include <numeric>

using namespace std;

class Solution {
public:
    long long dividePlayers(vector<int>& skill) {
        int sum = 0;
        multiset<int> skill_vals;
        for (int s : skill) {
            sum += s;
            skill_vals.insert(s);
        }

        int n = skill.size();
        int group_cnt = n / 2;
        if (sum % group_cnt != 0) {
            return -1;
        }

        long long rst = 0;
        int target = sum / group_cnt;
        for (int s : skill) {
            if (skill_vals.find(s) == skill_vals.end()) {
                continue;
            }

            skill_vals.erase(s);
            if (skill_vals.find(target - s) == skill_vals.end()) {
                return -1;
            }

            rst += s * (target - s);
            skill_vals.erase(target - s);
        }
        return rst;
    }
};

int main() {
    vector<int> skill({3,2,5,1,3,4});
    Solution s;
    s.dividePlayers(skill);
    return 0;
}
