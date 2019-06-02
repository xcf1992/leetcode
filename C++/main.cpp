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
#include <numeric>
using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> digit;
        int count = 1;
        for (int i = 1; i <= n; i++) {
            digit.push_back(i);
            count *= i;
        }
        
        string result = "";
        for (int i = 0; i != n; i++) {
            count = count / (n - i);
            int index = ((k - 1) / count) + 1;
            
            int available = 0;
            for (int pos = 0; pos < n; pos++) {
                if (digit[pos] == 0) {
                    continue;
                }
                
                available += 1;
                if (available < index) {
                    continue;
                }
                result.push_back('0' + digit[pos]);
                digit[pos] = 0;
            }
            k -= (index - 1) * count;
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({0,1,3,50,75});
    vector<vector<int>> matrix({
        {0,1,0},
        {1,1,1},
        {0,1,0}
    });
    s.getPermutation(3, 3);
}
