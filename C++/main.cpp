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

struct myComp {
    bool operator() (pair<int, int>& p1, pair<int, int>& p2) {
        return p1.first < p2.first || (p1.first == p2.first && p1.second > p2.second);
    }
};

class Solution {
private:
    void mergeCount(vector<int>& indices, int first, int last, vector<int>& result, vector<int>& nums) {
        int count = last - first;
        if (count <= 1) {
            return;
        }
        
        int mid = first + count / 2;
        mergeCount(indices, first, mid, result, nums);
        mergeCount(indices, mid, last, result, nums);
        
        vector<int> temp;
        int idx1 = first;
        int idx2 = mid;
        int semicount = 0;
        while (idx1 < mid or idx2 < last) {
            if (idx2 == last or (idx1 < mid and nums[indices[idx1]] <= nums[indices[idx2]])) {
                temp.push_back(indices[idx1]);
                result[indices[idx1]] += semicount;
                idx1 += 1;
            }
            else {
                temp.push_back(indices[idx2]);
                semicount += 1;
                idx2 += 1;
            }
        }
        move(temp.begin(), temp.end(), indices.begin() + first);
    }
public:
    vector<int> countSmaller(vector<int> nums) {
        int n = nums.size();
        vector<int> indices(n, 0);
        vector<int> result(n, 0);
        
        iota(indices.begin(), indices.end(), 0);
        mergeCount(indices, 0, n, result, nums);
        return result;
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({4,5,8,2});
    vector<int> vb({3,2});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    
    vector<vector<int>> matrix1({{1,2}, {0}, {0}});
    vector<vector<char>> matrix2({
        {'1','1','1','1','1','1','1','1'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','1','1','0'},
        {'1','1','1','1','1','0','0','0'},
        {'0','1','1','1','1','0','0','0'}
    });
    
    s.countSmaller({2,9,10});
    return 0;
}
