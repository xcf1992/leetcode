/*
 779. K-th Symbol in Grammar
 On the first row, we write a 0.
 Now in every subsequent row, we look at the previous row and replace each occurrence of 0 with 01,
 and each occurrence of 1 with 10.

 Given row N and index K,
 return the K-th indexed symbol in row N.
 (The values of K are 1-indexed.) (1 indexed).

 Examples:
 Input: N = 1, K = 1
 Output: 0

 Input: N = 2, K = 1
 Output: 0

 Input: N = 2, K = 2
 Output: 1

 Input: N = 4, K = 5
 Output: 1

 Explanation:
 row 1: 0
 row 2: 01
 row 3: 0110
 row 4: 01101001
 Note:

 N will be an integer in the range [1, 30].
 K will be an integer in the range [1, 2^(N-1)].
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
using namespace std;

/*
In particular, if we write say "0110" which generates "01101001",
then the first "0" generates the first "01" in the next row;
the next digit "1" generates the next "10",
the next "1" generates the next "10",
and the last "0" generates the last "01".

In general, the Kth digit's parent is going to be (K+1) / 2.
If the parent is 0, then the digit will be the same as 1 - (K%2).
If the parent is 1, the digit will be the opposite, ie. K%2.
*/
class Solution {
public:
    int kthGrammar(int N, int K) {
        if (N == 1) {
            return 0;
        }
        return kthGrammar(N - 1, (K + 1) / 2) ^ (K % 2 == 1 ? 0 : 1);
    }
};

class Solution {
private:
    int countDigit1(int num) {
        int result = 0;
        while (num != 0) {
            result += 1;
            num = num & (num - 1);
        }
        return result;
    }
public:
    int kthGrammar(int N, int K) {
        int count = countDigit1(K - 1);
        return (count & 1) == 0 ? 0 : 1;
    }
};
