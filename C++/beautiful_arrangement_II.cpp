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
    vector<int> constructArray(int n, int k) {
        vector<int> result;
        for (int i = 1, j = n; i <= j;) {
            if (k > 1) {
                result.push_back(k-- % 2 ? i++ : j--);
            }
            else {
                result.push_back(k % 2 ? i++ : j--);
            }
        }
        return result;
    }
};