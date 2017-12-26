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
public:
    string licenseKeyFormatting(string S, int K) {
        string result = "";
        int segment = 0;
        for (int i = S.size() - 1; i >= 0; i--) {
            char c = toupper(S[i]);
            if (c != '-') {
                result.insert(result.begin(), c);
                segment += 1;
                if (segment == K) {
                    segment = 0;
                    result.insert(result.begin(), '-');
                }
            }
        }

        int remove = 0;
        while (result[remove] == '-') {
            remove += 1;
        }
        return result.substr(remove);
    }
};