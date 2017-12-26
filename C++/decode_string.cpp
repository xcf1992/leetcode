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
    string decode(string& s, int& i) {
        string result;
        while (i < s.size() && s[i] != ']') {
            if (isalpha(s[i])) {
                result.push_back(s[i]);
            }
            else {
                int numStart = i;
                while (isdigit(s[i])) {
                    i++;
                }
                int repeat = stoi(s.substr(numStart, i - numStart));
                string word = decode(s, ++i);
                while (repeat > 0) {
                    result.append(word);
                    repeat--;
                }
            }
            i++;
        }

        return result;
    }
public:
    string decodeString(string s) {
        int i = 0;
        return decode(s, i);
    }
};

int main() {
    Solution s;
    cout << s.decodeString("3[a2[bc]]");
    return 0;
}