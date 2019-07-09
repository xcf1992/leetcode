/*
 1056. Confusing Number
 Given a number N, return true if and only if it is a confusing number, which satisfies the following condition:

 We can rotate digits by 180 degrees to form new digits. When 0, 1, 6, 8, 9 are rotated 180 degrees, they become 0, 1, 9, 8, 6 respectively. When 2, 3, 4, 5 and 7 are rotated 180 degrees, they become invalid. A confusing number is a number that when rotated 180 degrees becomes a different number with each digit valid.



 Example 1:



 Input: 6
 Output: true
 Explanation:
 We get 9 after rotating 6, 9 is a valid number and 9!=6.
 Example 2:



 Input: 89
 Output: true
 Explanation:
 We get 68 after rotating 89, 86 is a valid number and 86!=89.
 Example 3:



 Input: 11
 Output: false
 Explanation:
 We get 11 after rotating 11, 11 is a valid number but the value remains the same, thus 11 is not a confusing number.
 Example 4:



 Input: 25
 Output: false
 Explanation:
 We get an invalid number after rotating 25.


 Note:

 0 <= N <= 10^9
 After the rotation we can ignore leading zeros, for example if after rotation we have 0008 then this number is considered as just 8.
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
#include <set>
#include <numeric>
using namespace std;

class Solution {
public:
    bool confusingNumber(int N) {
        vector<int> rotate({0, 1, -1, -1, -1, -1, 9, -1, 8, 6});
        string num = to_string(N);
        int left = 0;
        int right = num.size() - 1;
        while (right >= left and num[right] == '0') {
            right -= 1;
        }

        while (left <= right) {
            if (rotate[num[left] - '0'] == -1 or rotate[num[right] - '0'] == -1) {
                return false;
            }

            swap(num[left], num[right]);
            num[right] = '0' + (rotate[num[right] - '0']);
            if (left != right) {
                num[left] = '0' + (rotate[num[left] - '0']);
            }
            left += 1;
            right -= 1;
        }
        return num != to_string(N);
    }
};
