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
#include "extra_data_types.hpp"
using namespace std;

class MajorityChecker {
private:
    unordered_map<int, vector<int>> index;
    vector<int> nums;
public:
    MajorityChecker(vector<int>& arr) {
        for (int i = 0; i < arr.size(); ++i) {
            index[arr[i]].push_back(i);
        }
        nums = arr;
        srand(time(NULL));
    }
    
    int query(int left, int right, int threshold) {
        int len = right - left + 1;
        for (int i = 0; i < 10; ++i) {
            int pick = nums[left + rand() % len];
            auto start = lower_bound(index[pick].begin(), index[pick].end(), left);
            if (start == index[pick].end()) {
                continue;
            }
            auto end = upper_bound(index[pick].begin(), index[pick].end(), left);
            if (end - start >= threshold) {
                return pick;
            }
        }
        return -1;
    }
};

int main() {
    vector<int> temp({1,1,2,2,1,1});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1},
        {1,2},
        {2,1},
        {1,0},
        {0,2},
        {0,0},
        {1,1}
    });
    vector<vector<int>> matrix2({
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
    });
    vector<string> words({"hot","dot","dog","lot","log","cog"});
    TreeNode* r1 = new TreeNode(0);
    TreeNode* r2 = new TreeNode(1);
    TreeNode* r3 = new TreeNode(3);
    r1 -> left = r2;
    
    MajorityChecker checker(temp);
    checker.query(0, 5, 4);
}
