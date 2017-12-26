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
    int countBinarySubstrings(string s) {
        int result = 0;
        int i = 1;
        char cur = s[0];
        int num = 1;
        while (i < s.size()) {
            if (s[i] == cur) {
                num += 1;
                i++;
            }
            else {
                int pos = i;
                int count = 0;
                while (s[i] == s[pos] && count < num && i < s.size()) {
                    i += 1;
                    count += 1;
                }

                result += count;
                num = 1;
                i = pos + 1;
                cur = s[pos];
            }
        }
        return result;
    }
};