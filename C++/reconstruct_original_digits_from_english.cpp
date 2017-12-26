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
    string originalDigits(string s) {
        vector<int> counts(26, 0);
        for (char c : s) {
            counts[c - 'a'] += 1;
        }

        vector<string> words = {"zero", "two", "four", "six", "eight", "one", "three", "five", "seven", "nine"};
        vector<int> nums = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
        vector<int> distinct = {'z', 'w', 'u', 'x', 'g', 'o', 'r', 'f', 'v', 'i'};
        string result;
        for (int i = 0; i < 10; i++) {
            string word = words[i];
            int count = counts[distinct[i] - 'a'];

            for (char c : word) {
                counts[c - 'a'] -= count;
            }

            while (count > 0) {
                result += to_string(nums[i]);
                count--;
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
};