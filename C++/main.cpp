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
    int oddEvenJumps(vector<int> A) {
        int n = A.size();
        vector<int> oddNext(n , -1);
        vector<int> evenNext(n , -1);
        map<int, int> numIndex;
        for (int i = n - 1; i >= 0; i--) {
            auto it = numIndex.lower_bound(A[i]); // >= A[i]
            if (it != numIndex.end()) {
                oddNext[i] = it -> second;
            }
            
            it = numIndex.upper_bound(A[i]);
            if (it != numIndex.begin() and --it != numIndex.end()) {
                evenNext[i] = it -> second;
            }
            numIndex[A[i]] = i;
        }

        vector<bool> odd(n, false);
        vector<bool> even(n, false);
        odd[n - 1] = even[n - 1] = true;
        int result = 1;
        for (int i = n - 2; i >= 0; i--) {
            if (oddNext[i] != -1) {
                odd[i] = even[oddNext[i]];
            }
            if (evenNext[i] != -1) {
                even[i] = odd[evenNext[i]];
            }
            if (odd[i]) {
                result += 1;
            }
        }
        return result;
    }
};


int main() {
    Solution s;
    cout << s.oddEvenJumps({5,5,5,6});
    return 0;
}
