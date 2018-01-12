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
    int findMaximumXOR(vector<int>& nums) {
        int result = 0;
        int mask = 0;
        unordered_set<int> values;
        for (int i = 31; i >= 0; i--) {
            values.clear();
            mask |= (1 << i);
            for (int num : nums) {
                values.insert(mask & num);
            }
            
            int temp = result | (1 << i);
            for (int value : values) {
                if (values.find(temp ^ value) != values.end()) {
                    result = temp;
                    break;
                }
            }
        }
        return result;
    }
};
