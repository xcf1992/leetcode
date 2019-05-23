class Solution {
public:
    vector<int> partitionLabels(string S) {
        vector<int> result;
        int sum = 0;
        unordered_map<char, int> labels;
        for (int i = 0; i < S.size(); i++) {
            char c = S[i];
            if (labels.find(c) == labels.end()) {
                labels[c] = i;
                result.push_back(1);
                sum += 1;
            }
            else {
                int pos = labels[c];
                int temp = i;
                while (temp > pos) {
                    temp -= result.back();
                    sum -= result.back();
                    result.pop_back();
                }
                result.push_back(i - sum + 1);
                sum += result.back();
                labels[c] = i;
            }
        }
        return result;
    }
};

class Solution1 {
private:
    vector<pair<int, int>> merge(vector<pair<int, int>>& intervals) {
        if (intervals.empty()) {
            return {};
        }
        
        vector<pair<int, int>> result;
        for (int i = 0; i < intervals.size(); i++) {
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