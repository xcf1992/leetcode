/*
 We have two integer sequences A and B of the same non-zero length.
 
 We are allowed to swap elements A[i] and B[i].  Note that both elements are in the same index position in their respective sequences.
 
 At the end of some number of swaps, A and B are both strictly increasing.  (A sequence is strictly increasing if and only if A[0] < A[1] < A[2] < ... < A[A.length - 1].)
 
 Given A and B, return the minimum number of swaps to make both sequences strictly increasing.  It is guaranteed that the given input always makes it possible.
 
 Example:
 Input: A = [1,3,5,4], B = [1,2,3,7]
 Output: 1
 Explanation:
 Swap A[3] and B[3].  Then the sequences are:
 A = [1, 3, 5, 7] and B = [1, 2, 3, 4]
 which are both strictly increasing.
 Note:
 
 A, B are arrays with the same length, and that length will be in the range [1, 1000].
 A[i], B[i] are integer values in the range [0, 2000].
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
/*
 Let me firstly explain the O(n) space DP solution which uses swapRecord[n] and fixRecord[n]. It would be more explicit.
 
 One thing should be kept in mind is, the array A and B would always be valid after you do the swap manipulation or not for each element. Take an example:
 
 index               0    1    2    3    4
 A                   1    3    5    4    9
 B                   1    2    3    7    10
 swapRecord          1    1    2    1    2
 fixRecord           0    0    0    2    1
 swapRecord[i] means for the ith element in A and B, the minimum swaps if we swap A[i] and B[i]
 fixRecord[i] means for the ith element in A and B, the minimum swaps if we DONOT swap A[i] and B[i]
 
 Obviously, swapRecord[0] = 1 and fixRecord[0] = 0.
 
 For i = 1, either swap or fix is OK. So we take the minimum previous result, min = min(swapRecord[0], fixRecord[0]) = 0. swapRecord[1] = min + 1 = 1, fixRecord[1] = min = 0
 For i = 2, notice that A[1] >= B[2], which means the manipulation of A[2] and B[2] should be same as A[1] and B[1], if A[1] and B[1] swap, A[2] and B[2] should swap, vice versa. Make sense, right? So swapRecord[2] = swapRecord[1] + 1 and fixRecord[2] = fixRecord[1]
 For i = 3, notice that A[2] >= A[3], which mean the manipulation of A[3] and B[3] and A[2] and B[2] should be opposite. In this case, swapRecord[3] = fixRecord[2] + 1 and fixRecord[3] = swapRecord[2]
 For the last elements, it's similiar as the elements when i = 1. Either swap or fix is OK. You can try to figure this out. :D
 
 Finally, we get the minimum of last swapRecord and fixRecord. It should be the result.
 
 Notice that every ith swapRecord and fixRecord is only relevant with the previous one. So the algorithm should be optimized to an O(1) space version. Just like the code I write above.
 */
class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int exchange = 1;
        int fix = 0;
        for (int i = 1; i < A.size(); i++) {
            if (A[i - 1] >= B[i] || B[i - 1] >= A[i]) {
                exchange += 1;
            }
            else if (A[i - 1] >= A[i] || B[i - 1] >= B[i]) {
                int temp = exchange;
                exchange = fix + 1;
                fix = temp;
            }
            else {
                int minSwap = min(exchange, fix);
                exchange = minSwap + 1;
                fix = minSwap;
            }
        }
        return min(fix, exchange);
    }
};
