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
    vector<int> findPermutation(string s) {
        vector<int> result;
        for (int i = 0; i <= s.size(); i++) {
            result.push_back(i + 1);
        }
        
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'D') {
                int right = i;
                while (right < s.size() && s[right] == 'D') {
                    right++;
                }
                
                int left = i;
                i = right;
                while (left < right) {
                    swap(result[left++], result[right--]);
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<string> v({"ABD","BCE","DEF","FFF"});
    vector<int> v2({2,2,2,2,2});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{78,16,94,36},{87,93,50,22},{63,28,91,60},{64,27,41,27},{73,37,12,69},{68,30,83,31},{63,24,68,36}});
    s.findPermutation("DDIIDI");
    
}
