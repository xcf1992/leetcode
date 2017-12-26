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
    vector<string> fizzBuzz(int n) {
        vector<string> result;

        for (int i = 1; i <= n; i++) {
            string word = "";
            if (i % 3 == 0) {
                word += "Fizz";
            }

            if (i % 5 == 0) {
                word += "Buzz";
            }

            if (word == "") {
                word = to_string(i);
            }
            
            result.push_back(word);
        }

        return result;
    }
};

int main() {
    Solution s;
    return 0;
}