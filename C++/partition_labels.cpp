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
