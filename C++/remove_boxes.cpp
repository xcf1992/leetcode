/*
 546. Remove Boxes
 Given several boxes with different colors represented by different positive numbers.
 You may experience several rounds to remove boxes until there is no box left.
 Each time you can choose some continuous boxes with the same color (composed of k boxes, k >= 1),
 remove them and get k*k points.
 Find the maximum points you can get.

 Example 1:
 Input:

 [1, 3, 2, 2, 2, 3, 4, 3, 1]
 Output:
 23
 Explanation:
 [1, 3, 2, 2, 2, 3, 4, 3, 1]
 ----> [1, 3, 3, 4, 3, 1] (3*3=9 points)
 ----> [1, 3, 3, 3, 1] (1*1=1 points)
 ----> [1, 1] (3*3=9 points)
 ----> [] (2*2=4 points)
 Note: The number of boxes n would not exceed 100.
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
 The initial thought is straightforward,
 try every possible removal and recursively search the rest.
 No doubt it will be a TLE answer.
 Obviously there are a lot of recomputations involved here.
 Memoization is the key then.

 But how to design the memory is tricky.
 I tried to use a string of 0s and 1s to indicate whether the box is removed or not, but still getting TLE.

 I think the problem of the approach above is that there are a lot of unnecessary computations (not recomputations).
 For example, if there is a formation of ABCDAA, we know the optimal way is B->C->D->AAA.
 On the other hand, if the formation is BCDAA, meaning that we couldn't find an A before D,
 we will simply remove AA,
 which will be the optimal solution for removing them.
 Note this is true only if AA is at the end of the array.
 With naive memoization approach,
 the program will search a lot of unnecessary paths,
 such as C->B->D->AA, D->B->C->AA.

 Therefore, I designed the memoization matrix to be memo[l][r][k],
 the largest number we can get using lth to rth (inclusive) boxes with k same colored boxes as rth box appended at the end.
 Example, memo[l][r][3] represents the solution for this setting: [b_l, ..., b_r, A,A,A] with b_r==A.

 The transition function is to find the maximum among all b_i == b_r for i=l,...,r-1:

 memo[l][r][k] = max(memo[l][r][k], memo[l][i][k+1] + memo[i+1][r-1][0])

 Basically, if there is one i such that b_i == b_r,
 we partition the array into two: [b_l, ..., b_i, b_r, A, ..., A],
 and [b_{i+1}, ..., b_{r-1}].
 The solution for first one will be memo[l][i][k+1],
 and the second will be memo[i+1][r-1][0].

 Otherwise, we just remove the last k+1 boxes (including b_r) and
 search the best solution for lth to r-1th boxes.
 (One optimization here: make r as left as possible,
 this improved the running time from 250ms to 35ms)

 The final solution is stored in memo[0][n-1][0] for sure.

 This can be better understood with the following example. Consider a subarray [x_l, x_{l+1},.., x_i,.., x_r, 6, 6, 6]
 For this subarray, if x_r=6, the entry at dp[l][r][3] represents the maximum points that can be obtained
 using the subarray boxes[l:r] if three 6's are appended with the trailing x_r

 Now, let us look at how to fill in the dpdp.
 Consider the same suabrray as mentioned above.
 For filling in the entry, dp[l][r][k], we firstly make an initial entry in dp[l][r][k],
 which considers the assumption that we will firstly combine the last k+1 similar elements
 and then proceed with the remaining subarray. Thus, the initial entry becomes:

 dp[l][r][k] = dp[l][r-1][0] + (k+1)*(k+1).

 Here, we combined all the trailing similar elements,
 so the value 0 is passed as the k value for the recursive function,
 since no similar elements to the (r−1)th element exist at its end.

But, the above situation isn't the only possible solution.
We could obtain a better solution for the same subarray boxes[l:r] for making the entry into dp[l][r][k],
if we could somehow combine the trailing similar elements with some extra similar elements lying between boxes[l:r].

Thus, we look for the elements within boxes[l:r], which could be similar to the trailing kk elements,
which in turn are similar to the rth element.
Whenever such an element boxes[i] is found,
we check if the new solution could lead to more points by using the same array.
If so, we update the entry at dp[l][r][k].

To get a clearer understanding of the above statment,
consider the same subarray again: [x_l, x_{l+1},.., x_i,.., x_r, 6, 6, 6] If x_i = x_r = 6
we could eventually be benefitted by combining x_i and x_r by removing the elements lying between them,
since now we can bring k+2 similar elements together.
By removing the in-between lying elements([x_{i+1}, x_{i+2},..., x_{r-1}],
the maximum points we can obtain are given by: dp[i+1][r-1][0].
Now, the points obtained from the remaining array [x_l, x_{l+1},.., x_i,x_r, 6, 6, 6]
are given by: dp[l][i][k+1], which is quite clear now.

Thus equation for dpdp updation becomes:
dp[l][r][k]=max(dp[l][r][k],dp[l][i][k+1]+dp[i+1][r-1][0]).
At the end, the entry for dp[0][n-1][0] gives the required result.
In the implementation below,
we've made use of calculatePoints function which is simply a recursive function used to obtain the dp values.
*/
class Solution {
private:
    int dfs(vector<int>& boxes, vector<vector<vector<int>>>& memo, int l, int r, int k) {
        if (l > r) {
            return 0;
        }
        if (memo[l][r][k] != 0) {
            return memo[l][r][k];
        }

        while (r > l && boxes[r - 1] == boxes[r]) {
            r -= 1;
            k += 1;
        }
        memo[l][r][k] = dfs(boxes, memo, l, r - 1, 0) + (k + 1) * (k + 1);
        for (int i = l; i < r; i++) {
            if (boxes[i] == boxes[r]) {
                memo[l][r][k] = max(memo[l][r][k], dfs(boxes, memo, l, i, k + 1) + dfs(boxes, memo, i + 1, r - 1, 0));
            }
        }
        return memo[l][r][k];
    }
public:
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        vector<vector<vector<int>>> memo(100, vector<vector<int>>(100, vector<int>(100, 0)));
        return dfs(boxes, memo, 0, n - 1, 0);
    }
};
