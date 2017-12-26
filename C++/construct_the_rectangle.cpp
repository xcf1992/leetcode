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
    vector<int> constructRectangle(int area) {
        vector<int> result;
        for (int i = sqrt(area); i > 0; i--) {
            if (area % i == 0) {
                result.push_back(area / i);
                result.push_back(i);
                break;
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    return 0;
}
