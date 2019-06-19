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
using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string> words, int maxWidth) {
        int n = words.size();
        vector<string> result;
        int count = 0;
        for (int i = 0; i < n; i += count) {
            int len = 0;
            count = 0;
            while (i + count < n and len + words[i + count].size() + count <= maxWidth) {
                len += words[i + count].size();
                count += 1;
            }
            
            string cur = words[i];
            for (int j = 1; j < count; ++j) {
                if (i + count > n) {
                    cur.push_back(' '); // last line we only need to insert one space between each word
                }
                else {
                    int spaceCount = (maxWidth - len) / (count - 1);
                    if (j - 1 < (maxWidth - len) % (count - 1)) {
                        spaceCount += 1;
                    }
                    cur += string(spaceCount, ' ');
                }
                cur += words[i + j];
            }
            cur += string(maxWidth - cur.size(), ' ');
            result.push_back(cur);
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({5,4,3,2,1});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1},
        {1,0}
    });
    s.fullJustify({"This", "is", "an", "example", "of", "text", "justification."}, 16);
}
