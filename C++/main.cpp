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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0;
        int right = arr.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == x) {
                left = mid;
                break;
            }
            else if (arr[mid] > x) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        
        int start = left;
        int end = left;
        while (end - start + 1 < k) {
            if (start >= 0 && (abs(x - arr[start]) < abs(x - arr[end]) || end >= arr.size())) {
                start -= 1;
            }
            else {
                end += 1;
            }
        }
        
        vector<int> result;
        for (int i = start; result.size() < k; i++) {
            result.push_back(arr[i]);
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({0,0,1,2,3,3,4,7,7,8});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{78,16,94,36},{87,93,50,22},{63,28,91,60},{64,27,41,27},{73,37,12,69},{68,30,83,31},{63,24,68,36}});
    s.findClosestElements(v2, 3, 5);
    
}
