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
    char map[255] = {0};

public:
    string reverseVowels(string s) {
        map['a'] = 1, map['e'] = 1, map['i'] = 1, map['o'] = 1, map['u'] = 1;
        map['A'] = 1, map['E'] = 1, map['I'] = 1, map['O'] = 1, map['U'] = 1;
        int left = 0;
        int right = s.size() - 1;

        while (left < right) {
            while (map[s[left]] == 0) {
                left += 1;
            }
            while (map[s[right]] == 0) {
                right -= 1;
            }
            if (left < right) {
                swap(s[left++], s[right--]);
            }
        }

        return s;
    }
};

int main() {
    Solution s;
    return 0;
}