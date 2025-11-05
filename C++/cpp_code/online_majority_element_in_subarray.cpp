/*
1157. Online Majority Element In Subarray
Implementing the class MajorityChecker, which has the following API:

MajorityChecker(int[] arr) constructs an instance of MajorityChecker with the given array arr;

int query(int left, int right, int threshold) has arguments such that:
0 <= left <= right < arr.length representing a subarray of arr;
2 * threshold > right - left + 1, ie. the threshold is always a strict majority of the length of the subarray

Each query(...) returns the element in arr[left], arr[left+1], ..., arr[right] that occurs at least threshold times,
or -1 if no such element exists.



Example:

MajorityChecker majorityChecker = new MajorityChecker([1,1,2,2,1,1]);
majorityChecker.query(0,5,4); // returns 1
majorityChecker.query(0,3,3); // returns -1
majorityChecker.query(2,3,2); // returns 2


Constraints:

1 <= arr.length <= 20000
1 <= arr[i] <= 20000
For each query, 0 <= left <= right < len(arr)
For each query, 2 * threshold > right - left + 1
The number of queries is at most 10000
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
#include <numeric>
using namespace std;
/*
Basic Idea
For each a in A, save its index of occurrence to list a2i[a].
When we want to get the exact occurrence of a in a range,
we can use binary search in a2i[a].

In the general good cases,
the numbers in A should be various,
each number should appear 1 time in average,
making the time complexity only O(1).

In the specific worst cases to this binary search solution,
the cases will be something like [1,2,1,2,1,2,1,2....],
making the binary search O(logN), (search in a list of length N / 2).

Now the only problem we need to solve,
is that how to find the majority element if it exists.


Solution 1: Random Pick
Random Pick number a from the range of query.
If there is a majority element,
we have >50% chance to get it for each pick.

Here I random pick 20 times,
because there are at most 10000 queries and 2^20 = 1048576 is much bigger than 10000.

If there is a majority element,
I only have 1/(2^20) possibility to miss it.
And we'll query at most 10000 times,
the expectation of fail times is about 0.01 time,
which sounds good.

I have used the same idea in 961. N-Repeated Element in Size 2N Array
The funny thing that, I was criticized this idea is misleading earlier this week.
Well thanks this guy and I recalled this idea immediately.

Complexity of function query:
Time O(20logN) for binary searching
Space O(1)
*/
class MajorityChecker {
private:
    unordered_map<int, vector<int> > index;
    vector<int> nums;

public:
    MajorityChecker(vector<int> &arr) {
        for (int i = 0; i < arr.size(); ++i) {
            index[arr[i]].push_back(i);
        }
        nums = arr;
        srand(time(NULL));
    }

    int query(int left, int right, int threshold) {
        int len = right - left + 1;
        for (int i = 0; i < 10; ++i) {
            int pick = nums[left + rand() % len];
            auto start = lower_bound(index[pick].begin(), index[pick].end(), left);
            if (start == index[pick].end()) {
                continue;
            }
            auto end = upper_bound(index[pick].begin(), index[pick].end(), right);
            if (end - start >= threshold) {
                return pick;
            }
        }
        return -1;
    }
};

/*
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
*/