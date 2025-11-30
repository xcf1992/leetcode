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
using namespace std;

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int result = 0;
        int i = 0;
        int j = 0;
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        while (i < g.size() and j < s.size()) {
            if (s[j] >= g[i]) {
                result += 1;
                i += 1;
                j += 1;
            } else {
                j += 1;
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}