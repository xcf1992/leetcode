/*
164. Maximum Gap

Given an unsorted array,
find the maximum difference between the successive elements in its sorted form.
Return 0 if the array contains less than 2 elements.

Example 1:
Input: [3,6,9,1]
Output: 3
Explanation: The sorted form of the array is [1,3,6,9], either
             (3,6) or (6,9) has the maximum difference 3.

Example 2:
Input: [10]
Output: 0
Explanation: The array contains less than 2 elements, therefore return 0.

Note:
You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
Try to solve it in linear time/space.
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
/*
Suppose for each of the n elements in our array, there was a bucket.
Then each element would occupy one bucket.
Now what if we reduced, the number of buckets?
Some buckets would have to accommodate more than one element.

Now let's talk about the gaps between the elements.
Let's take the best case,
where all elements of the array are sorted and have a uniform gap between them.
This means every adjacent pair of elements differ by the same constant value.
So for n elements of the array,
there are n-1 gaps, each of width, say, t.
It is trivial to deduce that t = (max - min)/(n-1)
(where max and minmin are the minimum and maximum elements of the array).
This width is the maximal width/gap between two adjacent elements in the array;
precisely the quantity we are looking for!

One can safely argue that this value of t, is in fact,
the smallest value that t can ever accomplish of any array with the same number of elements (i.e. n)
and the same range (i.e. (max - min).
To test this fact, you can start with a uniform width array (as described above)
and try to reduce the gap between any two adjacent elements.
If you reduce the gap between arr[i-1] and arr[i] to some value t - p,
then you will notice that the gap between arr[i] and arr[i+1] would have increased to t + p.
Hence the maximum attainable gap would have become t + p from t.
Thus the value of the maximum gap tt can only increase.

*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--
This (curMax - curMin) / (n - 1) would actually be the min(max gap),
if we pick randomly n numbers from [curMin, curMax]
As we put numbers into buckets
then the max Gap will only happen between adjacent bucket
cause gap between numbers in the same bucket will always smaller than (curMax - curMin) / (n - 1),
which make it cannot be the result
*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--

Coming back to our problem,
we have already established by application of the Pigeonhole Principle,
that if we used buckets instead of individual elements as our base for comparison,
the number of comparisons would reduce if we could accommodate more than one element in a single bucket.
That does not immediately solve the problem though.
What if we had to compare elements within a bucket?
We would end up no better.

So the current motivation remains:
somehow, if we only had to compare among the buckets,
and not the elements within the buckets, we would be good.
It would also solve our sorting problem:
we would just distribute the elements to the right buckets.
Since the buckets can be already ordered, and we only compare among buckets,
we wouldn't have to compare all elements to sort them!

But if we only had buckets to compare, we would have to ensure,
that the gap between the buckets itself represent the maximal gap in the input array.
How do we go about doing that?

We could do that just by setting the buckets to be smaller than t = (max - min)/(n-1) (as described above).
Since the gaps (between elements) within the same bucket would only be <= t,
we could deduce that the maximal gap would indeed occur only between two adjacent buckets.

Hence by setting bucket size bb to be 1 < b <= (max−min)/(n−1),
we can ensure that at least one of the gaps between adjacent buckets would serve as the maximal gap.

Algorithm

 - We choose a bucket size b such that 1 < b ≤ (max−min)/(n−1). Let's just choose b = ⌊(max−min)/(n−1)⌋.

 - Thus all the n elements would be divided among k = ⌈(max−min)/b⌉ buckets.

 - Hence the ith bucket would hold the range of values: [min + (i-1) * b, min + i*b) (1-based indexing).

 - It is trivial to calculate the index of the bucket to which a particular element belongs.
   That is given by ⌊(num−min)/b⌋ (0-based indexing) where num is the element in question.

 - Once all n elements have been distributed, we compare k-1 adjacent bucket pairs to find the maximum gap.
*/
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) {
            return 0;
        }

        int curMin = nums[0];
        int curMax = nums[0];
        for (int num : nums) {
            curMin = min(curMin, num);
            curMax = max(curMax, num);
        }

        int bucketSize = max(1, (curMax - curMin) / (n - 1));  // bucket size or capacity
        int bucketCount = (curMax - curMin) / bucketSize + 1;  // number of buckets
        vector<vector<int>> buckets(bucketCount, {0, INT_MAX, INT_MIN});
        // bucket_used, min_of_current_bucket, max_of_current_bucket
        for (int num : nums) {
            int index = (num - curMin) / bucketSize;
            buckets[index][0] = 1;
            buckets[index][1] = min(num, buckets[index][1]);
            buckets[index][2] = max(num, buckets[index][2]);
        }

        int result = 0;
        for (vector<int>& bkt : buckets) {
            if (bkt[0] == 0) {
                continue;
            }
            result = max(result, bkt[1] - curMin);
            curMin = bkt[2];
        }
        return result;
    }
};