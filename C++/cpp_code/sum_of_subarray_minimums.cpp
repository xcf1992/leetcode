/*
907. Sum of Subarray Minimums
https://leetcode.com/problems/sum-of-subarray-minimums/

Given an array of integers A, find the sum of min(B),
where B ranges over every (contiguous) subarray of A.

Since the answer may be large, return the answer modulo 10^9 + 7.

Example 1:
Input: [3,1,2,4]
Output: 17
Explanation: Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.  Sum is 17.

Note:
1 <= A.length <= 30000
1 <= A[i] <= 30000
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
I guess this is a general intuition for most solution.
res = sum(A[i] * f(i))
where f(i) is the number of subarrays,
in which A[i] is the minimum.

To get f(i), we need to find out:
left[i], the length of strict bigger numbers on the left of A[i],
right[i], the length of bigger numbers on the right of A[i].

Then,
left[i] + 1 equals to
the number of subarray ending with A[i],
and A[i] is single minimum.

right[i] + 1 equals to
the number of subarray starting with A[i],
and A[i] is the first minimum.

Finally f(i) = (left[i] + 1) * (right[i] + 1)

For [3,1,2,4] as example:
left + 1 = [1,2,1,1]
right + 1 = [1,3,2,1]
f = [1,6,2,1]
res = 3 * 1 + 1 * 6 + 2 * 2 + 4 * 1 = 17

Explanation:
To calculate left[i] and right[i],
we use two increasing stacks.

It will be easy if you can refer to this problem and my post:
901. Online Stock Span
I copy some of my codes from this solution.

Improvement
1.Here I record (A[i], count) in the stack.
We can also only record index.
2. For left part and right part, the logic is same.
So I used one stack and pass each.
This process can be optimized to one pass using one stack in total.

More:
For some more similar problem, I suggest
828. Unique Letter String
891. Sum of Subsequence Widths

Complexity:
All elements will be pushed twice and popped at most twice
O(N) time, O(N) space

as we can count duplicate minimum in the same subarry once
for example [3,1,1,2,4]
the subarray[1,1] should only be provide minimum 1 once
*/
class Solution {
private:
    int MOD = 1e9 + 7;

public:
    int sumSubarrayMins(vector<int>& A) {
        int n = A.size();
        vector<int> left(n, 0);
        vector<int> right(n, 0);
        stack<pair<int, int>> stk1, stk2;
        for (int i = 0; i < n; i++) {
            int count = 1;
            while (!stk1.empty() and stk1.top().first > A[i]) {
                // the count of number A[j] which > A[i], where j <= i
                count += stk1.top().second;
                stk1.pop();
            }
            stk1.push({A[i], count});
            left[i] = count;

            int j = n - 1 - i;
            count = 1;
            while (!stk2.empty() and stk2.top().first >= A[j]) {
                // the count of number A[j] which >= A[i], where j >= i
                count += stk2.top().second;
                stk2.pop();
            }
            stk2.push({A[j], count});
            right[j] = count;
        }

        long long result = 0;
        for (int i = 0; i < n; i++) {
            result = (result + (long long)A[i] * left[i] * right[i]) % MOD;
        }
        return result;
    }
};
/*
Before diving into the solution, we first introduce a very important stack type, which is called monotone stack .

What is monotonous increase stack?
Roughly speaking, the elements in the an monotonous increase stack keeps an increasing order.

The typical paradigm for monotonous increase stack:
for(int i = 0; i < A.size(); i++){
  while(!in_stk.empty() && in_stk.top() > A[i]){
    in_stk.pop();
  }
  in_stk.push(A[i]);
}
What can monotonous increase stack do?
(1) find the previous less element of each element in a vector with O(n) time:
What is the previous less element of an element?
For example:
[3, 7, 8, 4]
The previous less element of 7 is 3.
The previous less element of 8 is 7.
The previous less element of 4 is 3.
There is no previous less element for 3.
For simplicity of notation, we use abbreviation PLE to denote Previous Less Element.
(2) find the next less element of each element in a vector with O(n) time:
What is the next less element of an element?
For example:
[3, 7, 8, 4]
The next less element of 8 is 4.
The next less element of 7 is 4.
There is no next less element for 3 and 4.
For simplicity of notation, we use abbreviation NLE to denote Next Less Element.
How can the monotonous increase stack be applied to this problem?
For example:
Consider the element 3 in the following vector:

                            [2, 9, 7, 8, 3, 4, 6, 1]
                 |                    |
                 the previous less       the next less
                    element of 3          element of 3
After finding both NLE and PLE of 3, we can determine the
distance between 3 and 2(previous less) , and the distance between 3 and 1(next less).
In this example, the distance is 4 and 3 respectively.

How many subarrays with 3 being its minimum value?
The answer is 4*3.

9 7 8 3
9 7 8 3 4
9 7 8 3 4 6
7 8 3
7 8 3 4
7 8 3 4 6
8 3
8 3 4
8 3 4 6
3
3 4
3 4 6
How much the element 3 contributes to the final answer?
It is 3*(4*3).
What is the final answer?
Denote by left[i] the distance between element A[i] and its PLE.
Denote by right[i] the distance between element A[i] and its NLE.

The final answer is,
sum(A[i]*left[i]*right[i] )
 */

class Solution {
public:
    int sumSubarrayMins(vector<int>& A) {
        stack<pair<int, int>> in_stk_p, in_stk_n;
        // left is for the distance to previous less element
        // right is for the distance to next less element
        vector<int> left(A.size()), right(A.size());

        // initialize
        for (int i = 0; i < A.size(); i++)
            left[i] = i + 1;
        for (int i = 0; i < A.size(); i++)
            right[i] = A.size() - i;

        for (int i = 0; i < A.size(); i++) {
            // for previous less
            while (!in_stk_p.empty() && in_stk_p.top().first > A[i])
                in_stk_p.pop();
            left[i] = in_stk_p.empty() ? i + 1 : i - in_stk_p.top().second;
            in_stk_p.push({A[i], i});

            // for next less
            while (!in_stk_n.empty() && in_stk_n.top().first > A[i]) {
                auto x = in_stk_n.top();
                in_stk_n.pop();
                right[x.second] = i - x.second;
            }
            in_stk_n.push({A[i], i});
        }

        long long ans = 0, mod = 1e9 + 7;
        for (int i = 0; i < A.size(); i++) {
            ans = (ans + (long long)A[i] * left[i] * right[i]) % mod;
        }
        return ans;
    }
};

/*
In Implementation, Lee used another trick. Instead of doing a double pass to find the right and left boundary for the
current element. he calculate it only when an element is popped, when this happens we already have left and right
boundary for the popped element. This is Masterpiece
 */

class Solution {
public:
    int sumSubarrayMins(vector<int>& nums) {
        long long rst = 0;
        int n = nums.size();
        long long mod = 1e9 + 7;
        stack<int> max_stk;  // the top element is always with the largest value
        for (int i = 0; i <= n; i++) {
            int cur_val = i == n ? INT_MIN : nums[i];
            while (!max_stk.empty() && nums[max_stk.top()] > cur_val) {
                // we pop the stk and actually calculate the sum of subarray with minimum value as nums[mid_idx]
                // and the right boundary is current i, cause nums[i] < stk.top(), is the Next Less Element
                // left boundary is second top, as it is a decreasing stk, is the Previous Less Element
                int mid_idx = max_stk.top();
                max_stk.pop();

                int left_idx = -1;
                if (!max_stk.empty()) {
                    left_idx = max_stk.top();
                }

                rst = (rst + static_cast<long long>(nums[mid_idx]) * (mid_idx - left_idx) * (i - mid_idx)) % mod;
            }
            max_stk.push(i);
        }
        return static_cast<int>(rst);
    }
};
