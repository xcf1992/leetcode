/*
275. H-Index II

Given an array of citations sorted in ascending order
(each citation is a non-negative integer) of a researcher,
write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia:
"A scientist has index h if h of his/her N papers have at least h citations each,
 and the other N − h papers have no more than h citations each."

Example:

Input: citations = [0,1,3,5,6]
Output: 3
Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each of them had
             received 0, 1, 3, 5, 6 citations respectively.
             Since the researcher has 3 papers with at least 3 citations each and the remaining
             two with no more than 3 citations each, her h-index is 3.
Note:

If there are several possible values for h, the maximum one is taken as the h-index.

Follow up:

This is a follow up problem to H-Index, where citations is now guaranteed to be sorted in ascending order.
Could you solve it in logarithmic time complexity?

Follow up for H-Index: What if the citations array is sorted in ascending order? Could you optimize your algorithm?
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
 It takes me sometime to understand this question.
 Binary search is not difficult,
 the thing is how can we understand the meaning of c[m] < n - m and c[m] >= n - m,
 m is the middle index,
 n is the length of citations array,
 c is a abbreviation for citations array.

 To understand this we should have a clear understanding of the origin solution to this problem.
 It is on wikipage: https://en.wikipedia.org/wiki/H-index

 Summary here:
 Sort the array descending order, give each a index start from 1.
 From right to left, find the last number >= its index, the result is its index.

 …c: 25, 8, 5, 3, 3
 index:1, 2, 3, 4, 5
 number 5, H-index 3.

 After understand this origin solution, we can go to the binary search one.
 First, the different is the order changed, in this problem, the array sorted in ascending.
 We need somehow transfer it to original problem.

 For example, we have those number, and their index starts with 0
 …c: 3, 3, 5, 8, 25
 index: 0, 1, 2, 3, 4

 We can covert it using n the length of the array. We subtract n with the index, we get:
 …c: 3, 3, 5, 8, 25
 index0: 0, 1, 2, 3, 4
 index1: 5, 4, 3, 2, 1

 We can see we almost have the original form now except the order.
 It is easy, in the original problem we try to find the last one >= its index, now we find the first one >= its index.

 So now we just using binary search to find the number,
 a thing here we need to mind is the index0 here we are using,
 but we need to convert it to index1.
 */
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        int left = 0;
        int right = n - 1;
        while (left < right) {
            int mid = (right - left) / 2 + left;
            if (citations[mid] < n - mid) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        if (left < n && citations[left] >= n - left) {
            return n - left;
        }
        return 0;
    }
};

class Solution1 {
public:
    int hIndex(vector<int>& citations) {
        int index = 0;
        for (int i = citations.size() - 1; i >= 0; i--) {
            if (citations[i] > index) {
                index += 1;
            }
            else {
                break;
            }
        }
        return index;
    }
};
