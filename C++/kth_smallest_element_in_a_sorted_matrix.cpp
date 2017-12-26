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
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int size = matrix.size();
        int left = matrix[0][0];
        int right = matrix[size - 1][size - 1];

        while (left < right) {
            int smaller = 0;
            int middle = left + ((right - left) >> 1);
            
            for (int i = 0; i < size; i++) {
                smaller += upper_bound(matrix[i].begin(), matrix[i].end(), middle) - matrix[i].begin();
            }

            if (smaller < k) {
                left = middle + 1;
            }
            else {
                right = middle;
            }
        }

        return right;
    }
};

int main() {
    Solution s;
    return 0;
}