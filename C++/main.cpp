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
#include <numeric>
using namespace std;

class Solution {
private:
    int find(vector<int>& parent, int c) {
        int result = parent[c] == -1 ? c : find(parent, parent[c]);
        return result;
    }
public:
    bool equationsPossible(vector<string> equations) {
        vector<int> parent(26, -1);
        for (string& equation : equations) {
            if (equation[1] == '=') {
                int x = find(parent, equation[0] - 'a');
                int y = find(parent, equation[3] - 'a');
                parent[x] = y;
            }
        }

        for (string& equation : equations) {
            if (equation[1] == '!') {
                int x = find(parent, equation[0] - 'a');
                int y = find(parent, equation[3] - 'a');
                if (x == y) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    s.equationsPossible({"b==b","b==e","e==c","d!=e"});
    return 0;
}
