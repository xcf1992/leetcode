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

class Solution {
private:
    pair<string, vector<int>> parse(string str) {
        vector<int> count;
        string key = "";
        int prev = -1;
        int n = str.size();
        for (int i = 0; i < n; ++i) {
            if (i == n - 1 or str[i] != str[i + 1]) {
                key.push_back(str[i]);
                count.push_back(i - prev);
                prev = i;
            }
        }
        return {key, count};
    }
    
    bool check(pair<int, vector<int>>& s, pair<int, vector<int>>& word) {
        if (s.first != word.first) {
            return false;
        }
        
        vector<int> sCount = s.second;
        vector<int> wCount = word.second;
        for (int i = 0; i < sCount.size(); ++i) {
            if (sCount[i] < wCount[i] or (sCount[i] < 3 and sCount[i] != wCount[i])) {
                return false;
            }
        }
        return true;
    }
public:
    int expressiveWords(string S, vector<string>& words) {
        int n = words.size();
        if (n <= 0) {
            return 0;
        }
        
        pair<string, vector<int>> s = parse(S);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            pair<string, vector<int>> w = parse(words[i]);
            if (check(s, w)) {
                result += 1;
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({0,1,3,50,75});
    vector<vector<int>> matrix({
        {0,1,0},
        {1,1,1},
        {0,1,0}
    });
    
}
