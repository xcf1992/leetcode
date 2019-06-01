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
using namespace std;

class Solution {
private:
    bool isSub(const string a, const string b) {
        int i = 0;
        int j = 0;
        while (i < a.size() && j < b.size()) {
            if (a[i] == b[j]) {
                i++;
            }
            j++;
        }

        return i == a.size();
    }
public:
    int findLUSlength(vector<string>& strs) {
        sort(strs.begin(), strs.end(), [](const string a, const string b) {
            return a.size() > b.size();
        });

        unordered_map<string, int> count;
        for (string str : strs) {
            count[str] += 1;
        }

        for (int i = 0; i < strs.size(); i++) {
            if (count[strs[i]] != 1) {
                continue;
            }

            int j = 0;
            while (j < i) {
                if (isSub(strs[i], strs[j])) {
                    break;
                }
                j++;
            }
            if (j == i) {
                return strs[i].size();
            }
        }
        return -1;
    }
};
