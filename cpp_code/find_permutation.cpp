/*
484. Find Permutation

By now, you are given a secret signature consisting of character 'D' and 'I'.
'D' represents a decreasing relationship between two numbers,
'I' represents an increasing relationship between two numbers.
And our secret signature was constructed by a special integer array,
which contains uniquely all the different number from 1 to n
(n is the length of the secret signature plus 1).

For example, the secret signature "DI" can be constructed by array [2,1,3] or [3,1,2],
but won't be constructed by array [3,2,4] or [2,1,3,4],
which are both illegal constructing special string that can't represent the "DI" secret signature.

On the other hand, now your job is to find the lexicographically smallest permutation of [1, 2, ... n]
could refer to the given secret signature in the input.

Example 1:
Input: "I"
Output: [1,2]
Explanation: [1,2] is the only legal initial spectial string can construct secret signature "I",
where the number 1 and 2 construct an increasing relationship.

Example 2:
Input: "DI"
Output: [2,1,3]
Explanation: Both [2,1,3] and [3,1,2] can construct the secret signature "DI",
but since we want to find the one with the smallest lexicographical permutation, you need to output [2,1,3]
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
Let's revisit the important points of the given problem statement.
For a given n, we need to use all the integers in the range (1,n)
to generate a lexicographically smallest permutation of these n numbers which satsfies the pattern given in the string s.

Firstly, we note that the lexicographically smallest permutation that can be generated(irrelevant of the given pattern s)
using the n integers from (1,n) is [1, 2, 3,.., n](say min).
Thus, while generating the required permutation,
we can surely say that the permutation generated should be as close as possible to min.

Now, we can also note that the number generated will be the smallest possible
only if the digits lying towards the most significant positions are as small as possible
while satisfying the given pattern.
Now, to understand how these observations help in providing the solution of the given problem,
we'll look at a simple example.

Say, the given pattern ss is "DDIIIID".
This corresponds to n=8.
Thus, the minmin permutation possible will be [1, 2, 3, 4, 5, 6, 7, 8].
Now, to satisfy the first two "DD" pattern,
we can observe that the best course of action to generate the smallest arrangement will be to rearrange only 1, 2, 3,
because these are the smallest numbers that can be placed at the three most significant positions
to generate the smallest arrangement satisfying the given pattern till now,
leading to the formation of [3, 2, 1, 4, 5, 6, 7, 8] till now.
We can note that placing any number larger than 3 at any of these positions
will lead to the generation of a lexicographically larger arrangement as discussed above.

We can also note that irrespective of how we rearrange the first three 1, 2, 3,
the relationship of the last number among them with the next number always satisfies the criteria
required for satisfying the first I in s.
Further, note that, the pattern generated till now already satisfies the subpattern "IIII" in s.
This will always be satisfied since the min number considered originally always satisfies the increasing criteria.

Now, when we find the last "D" in the pattern ss,
we again need to make rearrangements in the last two positions only and
we need to use only the numbers 7, 8 in such rearrangements at those positions.
This is because, again, we would like to keep the larger number towards the least significant possible
as much as possible to generate the lexicographically smallest arrangement.
Thus, to satisfy the last "D" the best arrangement of the last two numbers is 8, 7
leading to the generation of [3, 2, 1, 4, 5, 6, 8, 7] as the required output.

Based on the above example, we can summarize that, to generate the required arrangement,
we can start off with the minmin number that can be formed for the given n.
Then, to satisfy the given pattern s,
we need to reverse only those subsections of the minmin array
which have a D in the pattern at their corresponding positions.

To perform these operations, we need not necessarily create the min array first,
because it simply consists of numbers from 1 to n in ascending order.

To perform the operations discussed above, we can make use of a stackstack.
We can start considering the numbers i from 1 to n.
For every current number,
whenver we find a D in the pattern s,
we just push that number onto the stackstack.
This is done so that, later on, when we find the next I,
we can pop off these numbers from the stack leading to the formation of a reversed (descending) subpattern of
those numbers corrresponding to the D's in ss(as discussed above).

When we encounter an I in the pattern, as discussed above,
we push the current number as well onto the stackstack and then pop-off all the numbers on the stackstack
and append these numbers to the resultant pattern formed till now.

Now, we could reach the end of the pattern s with a trail of D's at the end.
In this case, we won't find an ending I to pop-off the numbers on the stackstack.
Thus, at the end, we push the value n on the stack and then pop all the values on the stackstack
and append them to the resultant pattern formed till now.

Now, if the second last character in s was an I,
n will be appended at the end of the resultant arrangement correctly.
If the second last character was a D,
the reversed pattern appended at the end of the resultant arrangement will be reversed including the last number n.
In both the cases, the resultant arrangement turns out to be correct.
*/
class Solution {
public:
    vector<int> findPermutation(string s) {
        int n = s.size();
        vector<int> result(n + 1);
        iota(result.begin(), result.end(), 1);

        for (int i = 0; i < n; ++i) {
            if (s[i] == 'D') {
                int left = i;
                int right = i;
                while (right < n and s[right] == 'D') {
                    right += 1;
                }
                i = right - 1; // cause we will have i++ later

                while (left < right) {
                    swap(result[left], result[right]);
                    left += 1;
                    right -= 1;
                }
            }
        }
        return result;
    }
};
