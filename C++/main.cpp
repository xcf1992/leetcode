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
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int, int>> result;
        int curA = 0;
        int curB = 0;
        int nextA = 1;
        int nextB = 0;
        while (curA < nums1.size() && result.size() < k) {
            if (curA == nextA) {
                curB = nextB;
                nextA = curA + 1;
                nextB = 0;
            }
            if (nextA >= nums1.size() || nums1[curA] + nums2[curB] <= nums1[nextA] + nums2[nextB]) {
                result.push_back(make_pair(nums1[curA], nums2[curB]));
                if (curB == nums2.size() - 1) {
                    curA += 1;
                    curB = 0;
                }
                else {
                    curB += 1;
                }
            }
            else {
                swap(curA, nextA);
                swap(curB, nextB);
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> va({1,7,11});
    vector<int> vb({2,4,7});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{0,0,1,1}, {1,0,1,0}, {1,1,0,0}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(4,3));
    fuxk.push_back(make_pair(2,3));
    fuxk.push_back(make_pair(2,1));
    fuxk.push_back(make_pair(5,0));
    
    s.kSmallestPairs(va, vb, 100);
}
