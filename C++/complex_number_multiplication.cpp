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
    void decode(string number, vector<int>& factors) {
        int pos = number.find("+");
        string part1 = number.substr(0, pos);
        string part2 = number.substr(pos + 1, number.find("i") - pos - 1);
        
        factors.push_back(stoi(part1));
        factors.push_back(stoi(part2));
    }

public:
    string complexNumberMultiply(string a, string b) {
        vector<int> factors;
        decode(a, factors);
        int a1 = factors[0];
        int a2 = factors[1];

        factors.clear();
        decode(b, factors);
        int b1 = factors[0];
        int b2 = factors[1];

        string s1 = to_string(a1 * b1 - a2 * b2);
        string s2 = to_string(a2 * b1 + a1 * b2);

        return s1 + "+" + s2 + "i";
    }
};

int main() {
    Solution s;
    return 0;
}