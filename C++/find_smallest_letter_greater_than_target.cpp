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
    char nextGreatestLetter(vector<char>& letters, char target) {
        if (target >= letters.back()) {
            return letters.front();
        }
        
        int start = 0;
        int end = letters.size() - 1;
        int mid = start + (end - start) >> 1;
        while (start < end) {
            if (letters[mid] <= target) {
                start = mid + 1;
            }
            else {
                end = mid;
            }
            mid = start + (end - start) >> 1;
        }
        return letters[end];
    }
};
