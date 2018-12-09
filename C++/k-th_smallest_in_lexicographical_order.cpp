/*
 Given integers n and k, find the lexicographically k-th smallest integer in the range from 1 to n.
 
 Note: 1 ≤ k ≤ n ≤ 109.
 
 Example:
 
 Input:
 n: 13   k: 2
 
 Output:
 10
 
 Explanation:
 The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.
 Seen this question in a real interview before?
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

class Solution {
private:
    int find(int n, int k, int number, int& rank) {
        if (rank == k) {
            return number;
        }
        
        for (int digit = 0; digit <= 9; digit++) {
            int temp = number * 10 + digit;
            if (temp > n) {
                break;
            }
            rank += 1;
            int result = find(n, k, temp, rank);
            if (result != -1) {
                return result;
            }
        }
        return -1;
    }
public:
    int findKthNumber(int n, int k) {
        int rank = 0;
        int result = -1;
        for (int i = 1; i <= 9; i++) {
            if (i > n) {
                break;
            }
            rank += 1;
            result = find(n, k, i, rank);
            if (result != -1) {
                break;
            }
        }
        return result;
    }
};
