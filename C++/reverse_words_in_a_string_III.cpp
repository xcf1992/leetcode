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
    void reverse(string & word, int begin, int end) {
        while (begin < end) {
            swap(word[begin], word[end]);
            begin++;
            end--;
        }
    }
public:
    string reverseWords(string s) {
        int start = 0;
        int end = 0;

        while (end < s.size()) {
            while (s[end] != ' ') {
                end++;
            }

            reverse(s, start, end - 1);

            end += 1;
            start = end;
        }

        return s;
    }
};

int main() {
    Solution s;
    return 0;
}