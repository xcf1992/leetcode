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
private:
    vector<int> getMax(vector<int>& A, int start, int end, int length) {
        if (end - start < length) {
            return {};
        }
        
        vector<int> result(3, 0);
        for (int i = start; i < start + length; ++i) {
            result[2] += A[i];
        }
        result[0] = start;
        result[1] = start + length - 1;
        
        int cur = result[2];
        for (int i = start + length; i < end; ++i) {
            int temp = cur + A[i] - A[i - length];
            if (temp > result[2]) {
                result[2] = temp;
                result[0] = i - length + 1;
                result[1] = i;
            }
            cur = temp;
        }
        return result;
    }
    
    int getMaxSum(vector<int>& A, int L, int M) {
        int n = A.size();
        vector<int> maxL = getMax(A, 0, n, L);
        vector<int> maxM1 = getMax(A, 0, maxL[0], M);
        vector<int> maxM2 = getMax(A, maxL[1] + 1, n, M);
        int result = INT_MIN;
        if (!maxM1.empty()) {
            result = max(result, maxL[2] + maxM1[2]);
        }
        if (!maxM2.empty()) {
            result = max(result, maxL[2] + maxM2[2]);
        }
        return result;
    }
public:
    int maxSumTwoNoOverlap(vector<int> A, int L, int M) {
        return max(getMaxSum(A, L, M), getMaxSum(A, M, L));
    }
};

int main() {
    Solution s;
    s.maxSumTwoNoOverlap({8,20,6,2,20,17,6,3,20,8,12}, 5, 4);
    return 0;
}
