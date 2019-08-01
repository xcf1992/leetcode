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
#include "extra_data_types.hpp"
using namespace std;

class Solution { // binary search
private:
    vector<int> under(double limit, vector<int>& A) {
        double numer = 0.0;
        double denom = 1.0;
        int count = 0;
        int i = -1;
        int n = A.size();
        for (int j = 1; j < n; ++j) {
            // For each j, find the largest i so that primes[i] / primes[j] < x
            // It has to be at least as big as the previous i, so reuse it ("two pointer")
            while ((double)A[i + 1] < (double)A[j] * limit) {
                i += 1;
            }
            count += i + 1;
            // There are i+1 fractions: (primes[0], primes[j]),
            // (primes[1], primes[j]), ..., (primes[i], primes[j])
            if (i > 0 and numer * (double)A[j] < denom * (double)A[i]) {
                numer = A[i];
                denom = A[j];
            }
        }
        return {count, (int)numer, (int)denom};
    }
public:
    vector<int> kthSmallestPrimeFraction(vector<int> A, int K) {
        double left = 0;
        double right = 1;
        vector<int> result({0, 1});
        while (right - left > 1e-9) {
            double mid = left + (right - left) / 2;
            vector<int> smaller = under(mid, A);
            if (smaller[0] < K) {
                left = mid;
            }
            else {
                right = mid;
                result[0] = smaller[1];
                result[1] = smaller[2];
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    vector<int> temp({2,7,9,4,4});
    vector<int> temp1({1,3,3,3,2});
    vector<vector<int>> matrix({
        {0,1},
        {1,2},
        {2,1},
        {1,0},
        {0,2},
        {0,0},
        {1,1}
    });
    vector<vector<int>> matrix2({
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
    });
    vector<string> words({"hot","dot","dog","lot","log","cog"});
    TreeNode* r1 = new TreeNode(0);
    TreeNode* r2 = new TreeNode(1);
    TreeNode* r3 = new TreeNode(3);
    r1 -> left = r2;
    s.kthSmallestPrimeFraction({1, 7}, 1);
}
