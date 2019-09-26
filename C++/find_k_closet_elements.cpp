/*
658. Find K Closest Elements
https://leetcode.com/problems/find-k-closest-elements/

Given a sorted array, two integers k and x,
find the k closest elements to x in the array.
The result should also be sorted in ascending order.
If there is a tie, the smaller elements are always preferred.

Example 1:
Input: [1,2,3,4,5], k=4, x=3
Output: [1,2,3,4]

Example 2:
Input: [1,2,3,4,5], k=4, x=-1
Output: [1,2,3,4]

Note:
The value k is positive and will always be smaller than the length of the sorted array.
Length of the given array is positive and will not exceed 104
Absolute value of elements in the array and x will not exceed 104

UPDATE (2017/9/19):
The arr parameter had been changed to an array of integers (instead of a list of integers).
Please reload the code definition to get the latest changes.
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
using namespace std;
/*
Intuition
The array is sorted.
If we want find the one number closest to x,
we don't have to check one by one.
it's straightforward to use binary research.

Now we want the k closest,
the logic should be similar.

Explanation:
Assume we are taking A[i] ~ A[i + k - 1].
We can binary research i
We compare the distance between x - A[mid] and A[mid - k] - x

If x - A[mid] > A[mid + k] - x,
it means A[mid + 1] ~ A[mid + k] is better than A[mid] ~ A[mid + k - 1],
and we have mid smaller than the right i.
So assign left = mid + 1.

Note that, you shouldn't compare the absolute value abs(x - A[mid]) and abs(A[mid + k] - x).
It's wrong though it get accepetd.
It fails at the case A = [1,1,2,2,2,2,2,3,3], x=3, k=2

Time Complexity:
O(log(N - K)) to binary research and find reseult
O(K) to create the returned list.
*/
class Solution {
public:
    vector<int> findClosestElements(vector<int>& A, int k, int x) {
        int left = 0;
        int right = A.size() - k;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (x - A[mid] > A[mid + k] - x) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        return vector<int>(A.begin() + left, A.begin() + left + k);
    }
};

class Solution1 {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0;
        int right = arr.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] < x) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        } // left will point first number in arr >= x, could be replaced by left = lower_bound(arr.begin(), arr.end(), x) - arr.begin();

        int start = left - 1;
        int end = left;
        int temp = k;
        while (k > 0){
            if (start < 0 or (end < arr.size() and abs(arr[start] - x) > abs(arr[end] - x))) {
                end++;
            }
            else {
                start--;
            }
            k -= 1;
        }

        vector<int> result;
        for (int i = start + 1; result.size() < temp; i++) {
            result.push_back(arr[i]);
        }
        return result;
    }
};
