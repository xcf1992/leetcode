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
    bool checkRecord(string s) {
        int absent = 0;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == 'P') {
                continue;
            }
            if (c == 'A' and ++absent > 1) {
                return false;
            }
            if (i > 1 and s[i - 1] == 'L' and s[i - 2] == 'L') {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,3,2,4});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {1,0,1},
        {0,0,1}
    });
    vector<vector<int>> matrix2({
        {1,0},
        {0,0}
    });
    vector<string> words({"cat","cats","and","sand","dog"});
    s.checkRecord("PPPLPPLPPPLPPPPLPPPPLPPPLLALPP");
}
