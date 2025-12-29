/*
https://leetcode.com/problems/count-triplets-with-even-xor-set-bits-i/description/
3199. Count Triplets with Even XOR Set Bits I
Easy
Topics
conpanies icon
Companies
Hint
Given three integer arrays a, b, and c, return the number of triplets (a[i], b[j], c[k]), such that the bitwise XOR of
the elements of each triplet has an even number of set bits.


Example 1:

Input: a = [1], b = [2], c = [3]

Output: 1

Explanation:

The only triplet is (a[0], b[0], c[0]) and their XOR is: 1 XOR 2 XOR 3 = 002.

Example 2:

Input: a = [1,1], b = [2,3], c = [1,5]

Output: 4

Explanation:

Consider these four triplets:

(a[0], b[1], c[0]): 1 XOR 3 XOR 1 = 0112
(a[1], b[1], c[0]): 1 XOR 3 XOR 1 = 0112
(a[0], b[0], c[1]): 1 XOR 2 XOR 5 = 1102
(a[1], b[0], c[1]): 1 XOR 2 XOR 5 = 1102


Constraints:

1 <= a.length, b.length, c.length <= 100
0 <= a[i], b[i], c[i] <= 100
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
#include <climits>
#include <set>
using namespace std;

/*
Intuition
Take a[i] = 5 = (101), b[j] = 2 = (010), c[k] = 4 = (100) for example.

The result of whether a[i]^b[j]^c[k] = 3 = (011) has an even number of set bits is given by
(a[i][0]^b[j][0]^c[k][0]) ^ (a[i][1]^b[j][1]^c[k][1]) ^ (a[i][2]^b[j][2]^c[k][2])
(1 means odd and 0 means even). This is equivalent to
(a[i][0]^a[i][1]^a[i][2]) ^ (b[j][0]^b[j][1]^b[j][2]) ^ (c[k][0]^c[k][1]^c[k][2]) .

So we can compute the parity of set bits for each number separately and then XOR them together to determine the
outcomes.

Approach
Count the number of elements with odd/even set bits in each array.

The result count is either all three numbers with even set bits, or one with even and the other two with odd set bits.

Complexity
Time complexity: O(n⋅logM), where n is the average length of the arrays and M is the maximal number in the arrays.
Space complexity: O(1)
class Solution {
    public int tripletCount(int[] a, int[] b, int[] c) {
        // Preprocess arrays to count even and odd set bits
        int[] aCount = preprocess(a);
        int[] bCount = preprocess(b);
        int[] cCount = preprocess(c);

        // Calculate valid triplets
        int evenTriplets = aCount[0] * bCount[0] * cCount[0]; // even + even + even
        int oddOddEvenTriplets = aCount[1] * bCount[1] * cCount[0]; // odd + odd + even
        int oddEvenOddTriplets = aCount[1] * bCount[0] * cCount[1]; // odd + even + odd
        int evenOddOddTriplets = aCount[0] * bCount[1] * cCount[1]; // even + odd + odd

        // Total count of valid triplets
        return evenTriplets + oddOddEvenTriplets + oddEvenOddTriplets + evenOddOddTriplets;
    }

    // Method to preprocess array and count even and odd set bits
    private int[] preprocess(int[] arr) {
        int evenCount = 0;
        int oddCount = 0;
        // Iterate through array elements
        for (int num : arr) {
            // Count set bits and determine if even or odd
            if (Integer.bitCount(num) % 2 == 0) { // Check if number of set bits is even
                evenCount += 1; // Increment even count
            } else {
                oddCount += 1; // Increment odd count
            }
        }
        // Return counts of even and odd set bits
        return new int[]{evenCount, oddCount};
    }
}
 */
class Solution {
public:
    int tripletCount(vector<int>& a, vector<int>& b, vector<int>& c) {
        int rst = 0;
        for (int x : a) {
            for (int y : b) {
                for (int z : c) {
                    if (__builtin_popcount(x ^ y ^ z) % 2 == 0) {
                        rst += 1;
                    }
                }
            }
        }
        return rst;
    }
};