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
    int limit = 0;
    bool canDo(string stamp, string target, string current, int move, vector<int>& result, unordered_set<string>& mem) {
        if (move > limit) {
            return false;
        }
        
        if (mem.find(current) != mem.end()) {
            return false;
        }
        
        if (current == target) {
            return true;
        }
        
        for (int i = 0; i < target.size() - stamp.size(); i++) {
            if (result.empty() || i != result.back()) {
                string next = current;
                for (int j = 0; j < stamp.size(); j++) {
                    next[i + j] = stamp[j];
                }
                result.push_back(i);
                if (canDo(stamp, target, next, move + 1, result, mem)) {
                    return true;
                }
                mem.insert(next);
                result.pop_back();
            }
        }
        return false;
    }
public:
    vector<int> movesToStamp(string stamp, string target) {
        limit = 10 * target.size();
        string current = string(target.size(), '?');
        vector<int> result;
        unordered_set<string> mem;
        if (canDo(stamp, target, current, 0, result, mem)) {
            return result;
        }
        return {};
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<vector<int>> vb({{3,0}});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({
        {1,1,1,0,1,1,1,1},
        {1,0,0,0,0,1,1,1},
        {1,1,1,0,0,0,1,1},
        {1,1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0}
    });
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    vector<vector<int>> matrix3({
        {1,0},
        {0,1}
    });
    
    s.movesToStamp("abca", "aabcaca");
    return 0;
}
