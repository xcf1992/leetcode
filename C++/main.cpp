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
    string findReplaceString(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {
        vector<pair<int, int>> sortedIndex;
        for (int i = 0; i < indexes.size(); i++) {
            sortedIndex.push_back(make_pair(i, indexes[i]));
        }
        sort(sortedIndex.begin(), sortedIndex.end(), [](pair<int, int>& a, pair<int, int>& b) -> bool {
            return a.second > b.second;
        });
        
        for (pair<int, int>& index : sortedIndex) {
            int pos = index.second;
            int i = index.first;
            string s = sources[i];
            string t = sources[i];
            
            if (S.substr(pos, s.size()) == s) {
                S = S.substr(0, pos) + t + S.substr(pos + s.size());
            }
        }
        return S;
    }
};

int main() {
    Solution s;
    vector<string> v({"ahjpjau","ja","ahbwzgqnuk","tnmlanowax"});
    vector<int> v1({0,2});
    vector<string> v2({"a","cd"});
    vector<char> chars({'a','a','a','a','a','b','b','c'});
    vector<vector<int>> matrix({{1,2,2,3,5}, {3,2,3,4,4}, {2,4,5,3,1}, {6,7,1,4,5}, {5,1,1,2,4}});
    vector<pair<int, int>> fuxk;
    fuxk.push_back(make_pair(4,3));
    fuxk.push_back(make_pair(2,3));
    fuxk.push_back(make_pair(2,1));
    fuxk.push_back(make_pair(5,0));
    
    s.findReplaceString("abcd", v1, v2, v);
}
