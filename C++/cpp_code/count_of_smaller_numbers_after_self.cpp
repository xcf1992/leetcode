/*
315. Count of Smaller Numbers After Self

You are given an integer array nums and you have to return a new counts array.
The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:
Input: [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
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
count inversion
https://www.geeksforgeeks.org/counting-inversions/
*/
/*
 MergeSort-based solution is a standard way to solve problems related to inverse numbers.

 Here is an example to illustrate the general idea of MergeSort-based algorithm:

 Now we want to consider an array

 6 4 1 8 7 5 2 9
 First thing first, split the array into to subarrays:

 6 4 1 8
 7 5 2 9
 and then calculate the inverse numbers within the group:

 1 4(1) 6(1,4) 8
 2 5(2) 7(2,5) 9
 where the numbers in the parentheses are the numbers that should be counted when we calculate the inverse number.
 Now we need to merge these two arrays into one sorted array.

 The first element to be put into the sorted destination array is the "1" in the first array.
 1                  4(1) 6(1,4) 8
 2 5(2) 7(2,5) 9               merged elements in the 2nd array = ()

 The second element to merge is the "2" in the second array:
 1 2                4(1) 6(1,4) 8
 5(2) 7(2,5) 9               merged elements in the 2nd array = (2)

 The third element to merge is the "4" in the first array:
 1 2 4(1,2)              6(1,4) 8
 5(2) 7(2,5) 9               merged elements in the 2nd array = (2)
 When we merge the "4(1)", we found that "4" is actually greater than all merged elements in the second array (i.e.
[2]). Therefore, we also need to consider those elements. Therefore, the numbers in the parenthese of 2 become (1)+(2) =
(1,2).

 Next step:
 1 2 4(1,2) 5(2)         6(1,4) 8
 7(2,5) 9               merged elements in the 2nd array = (2,5)

 Next (add the inverse number of element "6" by 2)
 1 2 4(1,2) 5(2) 6(1,4,2,5)     8
 7(2,5) 9               merged elements in the 2nd array = (2,5)

 So and so forth, finally reach
 1 2 4(1,2) 5(2) 6(1,4,2,5) 7(2,5) 8(2,5,7) 9
 merged elements in the 2nd array = (2,5,7,9)
 Additionally, when we need to count the inverse number, we do not need to record the exact elements, we only need to
record the numbers. So, we can use a variable to record the number of "merged elements in the 2nd array" (for example,
semilen in the code beneath) and the number of smaller elements of each element (for example, results[idx] in the code
beneath).

To record the result,
we need to keep the index of each number in the original array.
So instead of sort the number in nums,
we sort the indexes of each number.

 Complexities:

 Time: O(n log n)

 Space: O(n)
*/
class Solution {
private:
    void mergeCount(vector<int>& indices, int first, int last, vector<int>& result, vector<int>& nums) {
        if (first >= last - 1) {
            return;
        }

        int mid = first + (last - first) / 2;
        mergeCount(indices, first, mid, result, nums);
        mergeCount(indices, mid, last, result, nums);

        vector<int> temp;
        int idx1 = first;
        int idx2 = mid;
        int semicount = 0;
        // semicount if the count of numbers have merged in second half before current number in first half
        while (idx1 < mid or idx2 < last) {
            if (idx2 == last or (idx1 < mid and nums[indices[idx1]] <= nums[indices[idx2]])) {
                temp.push_back(indices[idx1]);
                result[indices[idx1]] += semicount;
                idx1 += 1;
            } else {
                temp.push_back(indices[idx2]);
                semicount += 1;
                idx2 += 1;
            }
        }
        move(temp.begin(), temp.end(), indices.begin() + first);
    }

public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> indices(n, 0);
        iota(indices.begin(), indices.end(), 0);
        vector<int> result(n, 0);
        mergeCount(indices, 0, n, result, nums);
        return result;
    }
};