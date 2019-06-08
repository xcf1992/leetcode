/*
 870. Advantage Shuffle
 Given two arrays A and B of equal size, the advantage of A with respect to B is the number of indices i for which A[i] > B[i].
 
 Return any permutation of A that maximizes its advantage with respect to B.
 
 
 
 Example 1:
 
 Input: A = [2,7,11,15], B = [1,10,4,11]
 Output: [2,11,7,15]
 Example 2:
 
 Input: A = [12,24,8,32], B = [13,25,32,11]
 Output: [24,32,8,12]
 
 
 Note:
 
 1 <= A.length = B.length <= 10000
 0 <= A[i] <= 10^9
 0 <= B[i] <= 10^9
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <stdio.h>
#include <set>
using namespace std;

class Solution {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        map<int, int> count;
        for (int i : A) {
            count[i] += 1;
        }

        vector<int> result;
        for (int num : B) {
            auto it = count.upper_bound(num);
            if (it == count.end()) {
                it = count.begin();
            }

            result.push_back(it -> first);
            it -> second -= 1;
            if (it -> second == 0) {
                count.erase(it);
            }
        }
        return result;
    }
};

class Solution1 {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        int n = A.size();
        sort(A.begin(), A.end());
        
        int left = 0;
        int right = n - 1;
        vector<int> result(n, 0);
        vector<bool> used(n, false);
        for (int i = 0; i < n; i++) {
            if (B[i] > A[n - 1]) {
                while (left < n && used[left]) {
                    left += 1;
                }
                result[i] = A[left];
                used[left] = true;
            }
            else {
                int index = upper_bound(A.begin(), A.end(), B[i]) - A.begin();
                while (index < n && used[index]) {
                    index += 1;
                }
                if (index < n) {
                    result[i] = A[index];
                    used[index] = true;
                }
                else {
                    while (left < n && used[left]) {
                        left += 1;
                    }
                    result[i] = A[left];
                    used[left] = true;
                }
            }
        }
        
        return result;
    }
};
