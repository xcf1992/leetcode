/*
992. Subarrays with K Different Integers
https://leetcode.com/problems/subarrays-with-k-different-integers/

Given an array A of positive integers,
call a (contiguous, not necessarily distinct) subarray of A good
if the number of different integers in that subarray is exactly K.

(For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.)
Return the number of good subarrays of A.

Example 1:
Input: A = [1,2,1,2,3], K = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].

Example 2:
Input: A = [1,2,1,3,4], K = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].

Note:
1 <= A.length <= 20000
1 <= A[i] <= A.length
1 <= K <= A.length
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
Write a helper using sliding window,
to get the number of subarrays with at most K distinct elements.
Then f(exactly K) = f(atMost K) - f(atMost K-1).

Of course, you can merge 2 for loop into ones, if you like.
*/
class Solution {
private:
    int atMostK(vector<int> &A, int K) {
        int result = 0;
        int start = 0;
        unordered_map<int, int> count;
        for (int end = 0; end < A.size(); end++) {
            if (count[A[end]] == 0) {
                K -= 1;
            }
            count[A[end]] += 1;
            while (K < 0) {
                count[A[start]] -= 1;
                if (count[A[start]] == 0) {
                    K += 1;
                }
                start += 1;
            }
            // subarrays with at most K different elements, and the subarray end with end
            result += end - start + 1;
        }
        return result;
    }

public:
    int subarraysWithKDistinct(vector<int> &A, int K) {
        return atMostK(A, K) - atMostK(A, K - 1);
    }
};

/*
We used a map to keep track of the last apperance index of a character.
Then we move the right in outer layer to update the map.
If we have more than K element inside the window, move the left curosr, decrease number and update the map.
When the map have exactly K element, loop through the map to find out the minIndex of the map.

Any window start between [left, minIndex] and end with right is a qualified answer.
Time complexity O(NK), each element is put/pop from the sliding windows/map only once, each iteration might loop throguh all k element in the map.
Space complexity O(K), for the map keep track of last apperance of each K element.
*/
class Solution1 {
public:
    int subarraysWithKDistinct(vector<int> &A, int K) {
        int n = A.size();
        unordered_map<int, int> pos;
        int result = 0;
        int start = 0;
        int end = 0;
        while (end < n) {
            pos[A[end]] = end;
            while (pos.size() > K) {
                if (pos[A[start]] == start) {
                    pos.erase(A[start]);
                }
                start += 1;
            }

            /*
            * Because pos store the last index of each different number
            * thus number between left and end will be all the necessary number required
            * numbers between start and left will be all duplicated number with another half
            * so each subarray starts between start and left will be a valid subarray
            */
            if (pos.size() == K) {
                int left = end;
                for (auto it: pos) {
                    left = min(left, it.second);
                }
                result += left - start + 1;
                // Any window start between [start, left] and end with end is a qualified answer.
            }
            end += 1;
        }
        return result;
    }
};