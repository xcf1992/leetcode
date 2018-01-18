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
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private:
    bool dfs(string bottom, string curRow, int index, unordered_multimap<string, char> validBlock) {
        if (index == curRow.size()) {
            if (curRow.size() == 1) {
                return true;
            }
            string nextRow(curRow.size() - 1, 'Z');
            return dfs(curRow, nextRow, 0, validBlock);
        }
        
        string prefix(2, 'Z');
        prefix[0] = bottom[index];
        prefix[1] = bottom[index + 1];
        auto blocks = validBlock.equal_range(prefix);
        for (auto it = blocks.first; it != blocks.second; it++) {
            curRow[index] = it -> second;
            dfs(bottom, curRow, index + 1, validBlock);
        }
        return false;
    }
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        unordered_multimap<string, char> validBlock;
        for (string block : allowed) {
            validBlock.insert(pair<string, int>(block.substr(0, 2), block.back()));
        }
        string curRow(bottom.size() - 1, 'Z');
        return dfs(bottom, curRow, 0, validBlock);
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    cout << s.pyramidTransition("ABC", v) << endl;
}
