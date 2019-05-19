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
public:
    string boldWords(vector<string> words, string S) {
        int n = S.size();
        vector<bool> marked(n, false);
        for (string& word : words) {
            string temp = S;
            size_t pos = temp.find(word);
            while (pos != string::npos) {
                for (int j = 0; j < word.size(); ++j) {
                    marked[pos + j] = true;
                }
                pos = temp.find(word, pos + 1);
            }
        }
        
        string result = "";
        for (int i = 0; i < S.size(); i++) {
            if (marked[i] && (i == 0 || !marked[i - 1])) {
                result += "<b>";
            }
            
            result.push_back(S[i]);
            
            if (marked[i] && (i == S.size() - 1 || !marked[i + 1])) {
                result += "</b>";
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,10,100,1000});
    s.boldWords({"ccb","b","d","cba","dc"}, "eeaadadadc");
    return 0;
}
