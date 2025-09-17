/*
899. Orderly Queue

A string S of lowercase letters is given.
Then, we may make any number of moves.

In each move, we choose one of the first K letters (starting from the left),
remove it, and place it at the end of the string.

Return the lexicographically smallest string we could have after any number of moves.

Example 1:
Input: S = "cba", K = 1
Output: "acb"
Explanation:
In the first move, we move the 1st character ("c") to the end, obtaining the string "bac".
In the second move, we move the 1st character ("b") to the end, obtaining the final result "acb".

Example 2:
Input: S = "baaca", K = 3
Output: "aaabc"
Explanation:
In the first move, we move the 1st character ("b") to the end, obtaining the string "aacab".
In the second move, we move the 3rd character ("c") to the end, obtaining the final result "aaabc".

Note:
1 <= K <= S.length <= 1000
S consists of lowercase letters only.
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
If K == 1, we can only rotate the whole string.
There are S.length different states and
we return the lexicographically smallest string.

If K > 1, it means we can:
rotate the whole string,
rotate the whole string except the first letter.
012345 -> 023451 -> 034512 -> 045123 -> 051234

We can rotate i+1th big letter to the start (method 1),
then rotate ith big letter to the end (method 2).
2XXX01 -> XXX012

Actually, when K>=2,
we can prove that we can use the first 2 elements as a buffer to swap any two adjacent characters.
Since we can reach any permutation by swapping adjacent characters (like bubble sort),
in this case the minimal reachable permutation is the sorted S.

Assume that we want to swap S[i] and S[i+1],
we can first pop first i-1 characters to the end,
then pop i+1 and i, finally pop i+2~end.

Example:
K=2 S=bacdb Assume that we want to swap S[1] = a and S[2] = c

bacdb // initial
acdbb // pop first b to the end
dbbca // first pop S[2]=c, then pop S[1]=a
bbcad // pop S[3] = d
bcadb // pop S[4] = b, a and c are swapped!
*/
class Solution {
public:
    string orderlyQueue(string S, int K) {
        if (K > 1) {
            sort(S.begin(), S.end());
            return S;
        }

        string result = S;
        for (int i = 1; i < S.size(); i++) {
            result = min(result, S.substr(i) + S.substr(0, i));
        }
        return result;
    }
};
