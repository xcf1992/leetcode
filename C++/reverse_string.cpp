#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
using namespace std;


class Solution {
public:
    string reverseString(string s) {
        int start = 0;
        int end = s.size() - 1;
        while (end >= start) {
            swap(s[start], s[end]);
            start++;
            end--;
        }
        return s;
    }
};

int main() {
    Solution s;
    string test = "asdf";
    cout << test + "\n" << s.reverseString(test) << endl;
    return 0;
}
