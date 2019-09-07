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

class Solution {
private:
    vector<string> splitPhrase(string& phrase) { // return {first, middle, last}
        int n = phrase.size();
        vector<string> result(3, "");
        
        int left = 0;
        for (; left < n; ++left) {
            if (phrase[left] == ' ') {
                break;
            }
            result[0].push_back(phrase[left]);
        }
        left += 1;
        
        int right = n - 1;
        for (; right >= 0; --right) {
            if (phrase[right] == ' ') {
                break;
            }
            result[2].push_back(phrase[right]);
        }
        reverse(result[2].begin(), result[2].end());
        
        if (left < right) {
            result[1] = phrase.substr(left, right - left);
        }
        return result;
    }
public:
    vector<string> beforeAndAfterPuzzles(vector<string> phrases) {
        unordered_map<string, vector<pair<int, vector<string>>>> beginWtih;
        unordered_map<string, vector<pair<int, vector<string>>>> endWith;
        for (int i = 0; i < phrases.size(); ++i) {
            vector<string> tokens = splitPhrase(phrases[i]);
            beginWtih[tokens[0]].push_back({i, tokens});
            endWith[tokens[2]].push_back({i, tokens});
        }
        
        vector<string> result;
        for (auto& eIt: endWith) {
            string last = eIt.first;
            if (beginWtih.find(last) == beginWtih.end()) {
                continue;
            }
            
            vector<pair<int, vector<string>>>& endPhrases = eIt.second;
            vector<pair<int, vector<string>>>& beginPhrases = beginWtih[last];
            for (int i = 0; i < endPhrases.size(); ++i) {
                for (int j = 0; j < beginPhrases.size(); ++j) {
                    if (endPhrases[i].first == beginPhrases[j].first) {
                        continue;
                    }
                    
                    string part1 = endPhrases[i].second[0] + (endPhrases[i].second[1] == "" ? "" : " " + endPhrases[i].second[1]);
                    string part2 = beginPhrases[j].second[1] + (beginPhrases[j].second[1] == "" ? beginPhrases[j].second[2] : " " + beginPhrases[j].second[2]);
                    result.push_back(part1 + " " + last + " " + part2);
                }
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
};

int main() {
    Solution s;
    s.beforeAndAfterPuzzles({"a", "b", "a"});

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
