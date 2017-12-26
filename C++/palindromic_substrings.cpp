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
    int countSubstrings(string s) {
        int result = 0;
        int len = s.size();
        for (int mid = 0; mid < len; mid++) {
            result += 1;
            int left = mid - 1;
            int right = mid + 1;
            while (left >= 0 && right < len && s[left] == s[right]) {
                result += 1;
                left -= 1;
                right += 1;
            }
        }

        int midLeft = 0;
        int midRight = 1;
        while (midRight < len) {
            if (s[midLeft] == s[midRight]) {
                result += 1;
                int left = midLeft - 1;
                int right = midRight + 1;
                while (left >= 0 && right < len && s[left] == s[right]) {
                    result += 1;
                    left -= 1;
                    right += 1;
                }
            }
            midLeft += 1;
            midRight += 1;
        }
        return result;
    }
};