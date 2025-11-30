/*
444. Sequence Reconstruction

Check whether the original sequence org can be uniquely reconstructed from the sequences in seqs.
The org sequence is a permutation of the integers from 1 to n, with 1 ≤ n ≤ 104.
Reconstruction means building a shortest common supersequence of the sequences in seqs
(i.e., a shortest sequence so that all sequences in seqs are subsequences of it).
Determine whether there is only one sequence that can be reconstructed from seqs and it is the org sequence.

Example 1:
Input:
org: [1,2,3], seqs: [[1,2],[1,3]]
Output:
false
Explanation:
[1,2,3] is not the only one sequence that can be reconstructed, because [1,3,2] is also a valid sequence that can be
reconstructed.

Example 2:
Input:
org: [1,2,3], seqs: [[1,2]]
Output:
false
Explanation:
The reconstructed sequence can only be [1,2].

Example 3:
Input:
org: [1,2,3], seqs: [[1,2],[1,3],[2,3]]
Output:
true
Explanation:
The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct the original sequence [1,2,3].

Example 4:
Input:
org: [4,1,5,2,6,3], seqs: [[5,2,6,3],[4,1,5,2]]
Output:
true

UPDATE (2017/1/8):
The seqs parameter had been changed to a list of list of strings (instead of a 2d array of strings).
Please reload the code definition to get the latest changes.
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
#include <numeric>
using namespace std;
/*
For org to be uniquely reconstructible from seqs we need to satisfy 2 conditions:

Every sequence in seqs should be a subsequence in org. This part is obvious.

Every 2 consecutive elements in org should be consecutive elements in some sequence from seqs.
Why is that? Well, suppose condition 1 is satisfied.

Then for 2 any consecutive elements x and y in org we have 2 options.
We have both x and y in some sequence from seqs.
Then (as condition 1 is satisfied) they must be consecutive elements in this sequence.

There is no sequence in seqs that contains both x and y.
In this case we cannot uniquely reconstruct org from seqs
as sequence with x and y switched would also be a valid original sequence for seqs.

So this are 2 necessary criterions.
It is pretty easy to see that this are also sufficient criterions for org to be uniquely reconstructible
(there is only 1 way to reconstruct sequence when we know that condition 2 is satisfied).

To implement this idea I have idxs hash that maps item to its index in org sequence to check condition 1.
And I have pairs set that holds all consequitive element pairs for sequences from seqs to check condition 2
(I also consider first elements to be paired with previous undefined elements, it is necessary to check this).
*/
class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        if (seqs.empty()) {
            return false;
        }

        int n = org.size();
        vector<int> pos(n + 1, -1);
        for (int i = 0; i < n; ++i) {
            pos[org[i]] = i;
        }

        int matched = n - 1;
        bool allEmpty = true;
        vector<int> order(n + 1, -1);
        for (vector<int>& seq : seqs) {
            for (int i = 0; i < seq.size(); ++i) {
                allEmpty = false;
                if (seq[i] <= 0 or seq[i] > n or pos[seq[i]] == -1) {
                    return false;
                }
                if (i == 0) {
                    continue;
                }
                if (pos[seq[i - 1]] >= pos[seq[i]]) {
                    return false;
                }

                /*
                 * we only need to count each pair in org once, but they may appear in multiple seq more than once
                 * we we make order[seq[i - 1]] as 1 when have counted pair {org[seq[i - 1]], org[seq[i]]}
                 */
                if (pos[seq[i - 1]] == pos[seq[i]] - 1 and order[seq[i - 1]] == -1) {
                    matched -= 1;
                    order[seq[i - 1]] = 1;
                }
            }
        }
        return matched == 0 and !allEmpty;
    }
};