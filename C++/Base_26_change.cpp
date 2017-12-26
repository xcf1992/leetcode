#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    string convertToTitle(int n) {
        string result;
        vector<char> table;
        for (int i = 0; i < 26; i++) {
            table.push_back('A' + i);
        }

        while (n > 0) {
            string temp = "";
            temp += table[n % 26 - 1];
            result = temp + result;
            n = n / 26;
        }

        return result;
    }
};

int main() {
    Solution s;
    s.convertToTitle(1);
    return 0;
}