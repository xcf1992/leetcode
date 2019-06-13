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
    bool isValid(string s) {
        int count = 0;
        for (char c : s) {
            if (c == '(') {
                count += 1;
            }
            if (c == ')') {
                count -= 1;
            }
            if (count < 0) {
                return false;
            }
        }
        return count == 0;
    }
public:
    vector<string> removeInvalidParentheses(string s) {
        queue<string> bfs;
        unordered_set<string> visit;
        bfs.push(s);
        visit.insert(s);

        vector<string> result;
        int length = INT_MIN;
        while (!bfs.empty()) {
            string curS = bfs.front();
            bfs.pop();
            if (isValid(curS)) {
                if (curS.size() >= length) {
                    length = curS.size();
                    result.push_back(curS);
                }
                continue;
            }

            for (int i = 0; i < curS.size(); i++) {
                if (curS[i] != '(' && curS[i] != ')') {
                    continue;
                }

                string newS = curS.substr(0, i) + curS.substr(i + 1);
                if (visit.find(newS) == visit.end()) {
                    visit.insert(newS);
                    bfs.push(newS);
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,4,2,5,3});
    vector<vector<int>> matrix({
        {0,1,0},
        {1,1,1},
        {0,1,0}
    });
    s.removeInvalidParentheses("()())()");
}
