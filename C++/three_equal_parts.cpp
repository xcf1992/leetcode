/*
 927. Three Equal Parts
 Given an array A of 0s and 1s, divide the array into 3 non-empty parts such that all of these parts represent the same binary value.

 If it is possible, return any [i, j] with i+1 < j, such that:

 A[0], A[1], ..., A[i] is the first part;
 A[i+1], A[i+2], ..., A[j-1] is the second part, and
 A[j], A[j+1], ..., A[A.length - 1] is the third part.
 All three parts have equal binary value.
 If it is not possible, return [-1, -1].

 Note that the entire part is used when considering what binary value it represents.  For example, [1,1,0] represents 6 in decimal, not 3.  Also, leading zeros are allowed, so [0,1,1] and [1,1] represent the same value.



 Example 1:

 Input: [1,0,1,0,1]
 Output: [0,3]
 Example 2:

 Input: [1,1,0,1,1]
 Output: [-1,-1]


 Note:

 3 <= A.length <= 30000
 A[i] == 0 or A[i] == 1
 */
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

/*
 The basic idea if the result exists then every part should have the same number of 1
 we find the start and end pos of 1 in each part and check if the number created is equal
 Besides, we need to confirm that
 number of 0 after last 1 in each part should be bigger than or eauql to
 the tail 0 of the third part
 */
class Solution {
private:
    bool isEqual(vector<int>& A, int s1, int e1, int s2, int e2, int s3, int e3) {
        string num1 = getNum(A, s1, e1);
        string num2 = getNum(A, s2, e2);
        string num3 = getNum(A, s3, e3);
        return num1 == num2 and num1 == num3;
    }

    string getNum(vector<int>& A, int start, int end) {
        string num = "";
        for (int i = start; i <= end; i++) {
            num.push_back('0' + A[i]);
        }
        return num;
    }
public:
    vector<int> threeEqualParts(vector<int> A) {
        int total = 0;
        for (int a : A) {
            total += a;
        }

        if (total % 3 != 0) {
            return {-1, -1};
        }
        int n = A.size();
        int ones = total / 3;
        if (ones == 0) {
            return {0, n - 1};
        }

        int count = 0;
        int s1 = -1, e1 = -1;
        int s2 = -1, e2 = -1;
        int s3 = -1, e3 = -1;
        for (int i = 0; i < n; i++) {
            if (A[i] == 1) {
                count += 1;

                if (count == 1) {
                    s1 = i;
                }
                // we use if but not else if here because it may happen that start and end at the same pos
                if (count == ones) {
                    e1 = i;
                }
                if (count == ones + 1) {
                    s2 = i;
                }
                if (count == 2 * ones) {
                    e2 = i;
                }
                if (count == 2 * ones + 1) {
                    s3 = i;
                }
                if (count == 3 * ones) {
                    e3 = i;
                }
            }
        }

        if (!isEqual(A, s1, e1, s2, e2, s3, e3)) {
            return {-1, -1};
        }

        int gap1 = s2 - e1 - 1;
        int gap2 = s3 - e2 - 1;
        int gap3 = n - e3 - 1;
        if (gap1 < gap3 or gap2 < gap3) {
            return {-1, -1};
        }
        // the returned resuult is e1 + gap3 and e2 + gap3 + 1
        // becuase the second part is A[i+1], A[i+2], ..., A[j-1]
        return {e1 + gap3, e2 + gap3 + 1};
    }
};
