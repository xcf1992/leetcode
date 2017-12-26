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
    void reverse(string& s, int start, int k) {
        if (start >= s.size()) {
            return;
        }
        int begin = start;
        int end = start;
        if (s.size() - start < k) {
            end = s.size() - 1;
        }
        else {
            end = start + k - 1;
        }

        while (begin <= end) {
            swap(s[begin], s[end]);
            begin += 1;
            end -= 1;
        }

        reverse(s, start + 2k, k);
    }
public:
    string reverseStr(string s, int k) {
        reverse(s, 0, k);
        return s;
    }
};