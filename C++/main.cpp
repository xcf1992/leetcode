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
    int findSubstringInWraproundString(string p) {
        int n = p.size();
        if (n < 2) {
            return n;
        }
        
        vector<int> counts(26, 0);
        int start = 0;
        int end = 1;
        while (end <= n) {
            int a = p[end] - 'a' + 1;
            int b = p[end - 1] - 'a';
            while (end < n && (p[end] - 'a' + 1) % 26 == (p[end - 1] - 'a')) {
                end += 1;
            }
            while (start < end) {
                counts[p[start] - 'a'] = max(end - start, counts[p[start] - 'a']);
                start += 1;
            }
            end += 1;
        }
        
        int result = 0;
        for (int count : counts) {
            result += count;
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> v1({1,0,0,0,0,1});
    vector<int> v2({0,4});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{1,2,2,3,5}, {3,2,3,4,4}, {2,4,5,3,1}, {6,7,1,4,5}, {5,1,1,2,4}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(4,3));
    fuxk.push_back(make_pair(2,3));
    fuxk.push_back(make_pair(2,1));
    fuxk.push_back(make_pair(5,0));
    
    s.findSubstringInWraproundString("abcdzab");
}
