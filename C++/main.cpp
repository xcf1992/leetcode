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
    vector<pair<int, int>> merge(vector<pair<int, int>>& intervals) {
        if (intervals.empty()) {
            return {};
        }

        vector<pair<int, int>> result;
        for (int i = 1; i < intervals.size(); i++) {
            if (!result.empty() and result.back().second > intervals[i].first) {
                result.back().second = max(result.back().second, intervals[i].second);
            }
            else {
                result.push_back(intervals[i]);
            }
        }
        return result;
    }
public:
    vector<int> partitionLabels(string S) {
        vector<vector<int>> letter(26);
        int index = 0;
        for (char c : S) {
            letter[c - 'a'].push_back(index);
            index += 1;
        }

        vector<pair<int, int>> intervals;
        for (vector<int>& l : letter) {
            if (!l.empty()) {
                intervals.push_back({l.front(), l.back()});
            }
        }

        sort(intervals.begin(), intervals.end(), [](pair<int, int>& a, pair<int, int>& b) {
            return a.first < b.first or (a.first == b.first and a.second < b.second);
        });
        vector<pair<int, int>> partitions = merge(intervals);

        vector<int> result;
        for (pair<int, int>& p : partitions) {
            result.push_back(p.second - p.first + 1);
        }
        return result;
    }
};

int main() {
    int x = stoi("-100");
    Solution s;
    vector<int> temp({1,10,100,1000});
    s.partitionLabels("ababcbacadefegdehijhklij");
}
