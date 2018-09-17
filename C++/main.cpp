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
public:
    int totalFruit(vector<int> tree) {
        int result = 0;
        int typ1 = -1;
        int typ2 = -1;
        int count = 0;
        int idx1 = -1;
        int idx2 = -1;
        for (int pos = 0; pos < tree.size(); pos++) {
            if (typ1 == -1) {
                typ1 = tree[pos];
                count += 1;
                idx1 = pos;
            }
            else if (typ2 == -1) {
                typ2 = tree[pos];
                count += 1;
                idx2 = pos;
            }
            else if (typ1 == tree[pos]) {
                count += 1;
                idx1 = pos;
            }
            else if (typ2 == tree[pos]) {
                count += 1;
                idx2 = pos;
            }
            else {
                if (idx2 < idx1) {
                    swap(idx1, idx2);
                    swap(typ1, typ2);
                }
                
                result = max(result, count);
                count = pos - idx1;
                typ1 = tree[pos];
                idx1 = pos;
            }
        }
        return max(count, result);
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<int> vb({3,2});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({{1,0,2,0,1}, {0,0,0,0,0}, {0,0,1,0,0}});
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    
    s.totalFruit({0,0,1,1});
    return 0;
}
