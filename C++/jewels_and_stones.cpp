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
    int numJewelsInStones(string J, string S) {
        unordered_set<char> jewels;
        for (char c : J) {
            jewels.insert(c);
        }

        int result = 0;
        for (char c : S) {
            result += jewels.count(c);
        }
        return result;
    }
};