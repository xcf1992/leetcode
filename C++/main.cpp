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
#include <map>
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size();
        int index = 0;
        for (int i = 0; i < n; ++i) {
            if (arr[i] == 0) {
                index += 1;
            }
            index += 1;
        }
        index -= 1;
        
        for (int i = n - 1; i >= 0; --i) {
            if (index <= n - 1) {
                arr[index] = arr[i];
            }
            index -= 1;
            if (arr[i] == 0) {
                if (index <= n - 1) {
                    arr[index] = 0;
                }
                index -= 1;
            }
        }
        return;
    }
};

int main() {
    Solution s;
    vector<int> temp({1,0,2,3,0,4,5,0});
    vector<vector<int>> matrix({
        {0,1,0},
        {1,1,1},
        {0,1,0}
    });
    s.duplicateZeros(temp);
}
