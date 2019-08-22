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

class NumArray { // segment tree
private:
    TreeNode* root;
    vector<int> nums;

    TreeNode* build(int start, int end, vector<int>& nums) {
        if (start == end) {
            return new TreeNode(nums[start]);
        }

        TreeNode* cur = new TreeNode(0);
        int mid = start + (end - start) / 2;
        cur -> left = build(start, mid, nums);
        cur -> right = build(mid + 1, end, nums);
        cur -> val = cur -> left -> val + cur -> right -> val;
        return cur;
    }

    void update(int start, int end, int index, int val, TreeNode* cur) {
        if (start == end) {
            cur -> val = val;
            return;
        }

        int mid = start + (end - start) / 2;
        if (start <= index and index <= mid) {
            update(start, mid, index, val, cur -> left);
        }
        else {
            update(mid + 1, end, index, val, cur -> right);
        }
        cur -> val = cur -> left -> val + cur -> right -> val;
    }

    int query(int start, int end, int left, int right, TreeNode* cur) {
        if (start > right or left > end) {
            return 0;
        }

        if (left <= start and end <= right) {
            return cur -> val;
        }

        int mid = start + (end - start) / 2;
        return query(start, mid, left, right, cur -> left) + query(mid + 1, end, left, right, cur -> right);
    }
public:
    NumArray(vector<int> nums) {
        nums = nums;
        root = build(0, nums.size() - 1, nums);
    }

    void update(int i, int val) {
        update(0, nums.size() - 1, i, val, root);
    }

    int sumRange(int i, int j) {
        return query(0, nums.size() - 1, i, j, root);
    }
};

int main() {
    NumArray nums({1,3,5});
    nums.update(0, 2);
    nums.update(1, 2);
    nums.sumRange(0, 2);

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
}
