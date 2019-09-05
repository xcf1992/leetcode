/*
 793. Preimage Size of Factorial Zeroes Function
 Let f(x) be the number of zeroes at the end of x!. (Recall that x! = 1 * 2 * 3 * ... * x, and by convention, 0! = 1.)

 For example, f(3) = 0 because 3! = 6 has no zeroes at the end,
 while f(11) = 2 because 11! = 39916800 has 2 zeroes at the end.
 Given K, find how many non-negative integers x have the property that f(x) = K.

 Example 1:
 Input: K = 0
 Output: 5
 Explanation: 0!, 1!, 2!, 3!, and 4! end with K = 0 zeroes.

 Example 2:
 Input: K = 5
 Output: 0
 Explanation: There is no x such that x! ends in K = 5 zeroes.
 Note:

 K will be an integer in the range [0, 10^9].
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
#include <set>
using namespace std;
/*
 Since the steps of the jump may be greater than 1,
 not all integer values can be taken by K.

 For example, K cannot be 5 as the step at x = 25 is two so K will jump from 4 directly to 6,
 thus skip the middle value of 5 (see the red dashed line between two brown lines in the above plot).

 We shall call these skipped integers as invalid values for K
 and conclude there are NO integers x such that x! has K trailing zeros at these K values.

 Furthermore, for each valid K value, there will be exactly FIVE integers x such that x! has K trailing zeros
 (this is because if x is an integer multiple of 5, then x+1, x+2, x+3, x+4 will have no factor of 5,
 thus the jump step at each of these points will be 0, which implies K will remain the same in the range [x, x+4]).
 In summary, we conclude the number of integers x such that x! has K trailing zeros will be either 0 or 5,
 where the former corresponds to invalid K values while the latter corresponds to valid K values.

 As a direct result of the above observation, all the valid K values will form an ordered list of ranges
 where each range consists of 5 continuous integers, i.e., the valid K values are: [0, 5), [6, 11), [12, 17), …, etc.
 The K values will break up whenever x is an integer multiple of 25
 and the size(i.e., number of elements) of the gap between the two separated ranges
 will be given by the number of factor 5 in x minus 1
(note it’s the number of factor minus 1, not x, and is equivalent to the number of factor 5 in x/5).

 Let K = numOfTrailingZeros(x), then K will jump whenever x is an integer multiple of 5
 (this is a direct result of the fact that the number of factor 5 in x! will change whenever x is an integer multiple of 5).
 The step of the jump will be given by the number of factor 5 in x (no factorial).
 For example, K will jump by 1 step at x = 5, 10, 15, 20, but by 2 steps at 25, as demonstrated in the following plot:
*/
class Solution {
private:
    long trailingZeros(long x) {
        long count = 0;
        while (x != 0) {
            count += x / 5;
            x /= 5;
        }
        return count;
    }
public:
    int preimageSizeFZF(long K) {
        long left = 0;
        long right = 5 * (K + 1);
        while (left <= right) {
            long mid = (right - left) / 2 + left;
            long count = trailingZeros(mid);

            if (count == K) {
                return 5;
            }
            else if (count > K) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return 0;
    }
};

/*
 This solution takes advantage of the last observation mentioned above,
 where we use binary search to find the largest integers x and y such that numOfTrailingZeros(x) <= K
 and numOfTrailingZeros(y) <= K-1, respectively.
 Then the factorial of all integers in the range (y, x] (left exclusive, right inclusive) will have K trailing zeros.
 Therefore the total number of non-negative integers whose factorials have K trailing zeros will be given by x - y.

 The following is the Java code for this solution, where the time complexity is O((logK)^2)
 and space complexity is O(1).
 Note that x! will always have at least x/5 trailing zeros,
 therefore, if y is the largest integer such that y! has no more than K trailing zeros,
 then we have y <= 5 * (K + 1), which can serve as the upper bound of our binary search.
*/
class Solution1 {
private:
    long trailingZeros(long x) {
        long count = 0;
        while (x != 0) {
            count += x / 5;
            x /= 5;
        }
        return count;
    }

    long search(long K) {
        long left = 0;
        long right = 5 * (K + 1);

        while (left <= right) {
            long mid = (right - left) / 2 + left;
            long count = trailingZeros(mid);

            if (count <= K) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return left;
    }
public:
    int preimageSizeFZF(int K) {
        int result = 0;
        return search(K) - search(K - 1);
    }
};
