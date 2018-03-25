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
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    bool placeFlower(vector<int> bed, int flower, int start) {
        if (flower <= 0) {
            return true;
        }
        
        if (start >= bed.size()) {
            return false;
        }
        
        for (int i = start; i < bed.size(); i++) {
            if (bed[i] == 0) {
                if ((i - 1 < start || bed[i - 1] == 0) && (i + 1 >= bed.size() || bed[i + 1] == 0)) {
                    bed[i] = 1;
                    if (placeFlower(bed, flower - 1, i + 1)) {
                        return true;
                    }
                    bed[i] = 0;
                }
            }
        }
        
        return false;
    }
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        if (n == 0) {
            return true;
        }
        
        if (n > (flowerbed.size() + 1) / 2) {
            return false;
        }
        return placeFlower(flowerbed, n, 0);
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v1({1,0,0,0,0,1});
    vector<int> v2({0,4});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{0,0,1,0,0}, {0,0,0,0,0}, {0,0,0,1,0}, {1,1,0,1,1}, {0,0,0,0,0}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(4,3));
    fuxk.push_back(make_pair(2,3));
    fuxk.push_back(make_pair(2,1));
    fuxk.push_back(make_pair(5,0));
    
    s.canPlaceFlowers(v1, 2);
}
