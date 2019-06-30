/*
 996. Number of Squareful Arrays

 Given an array A of non-negative integers, the array is squareful if for every pair of adjacent elements, their sum is a perfect square.

 Return the number of permutations of A that are squareful.  Two permutations A1 and A2 differ if and only if there is some index i such that A1[i] != A2[i].



 Example 1:

 Input: [1,17,8]
 Output: 2
 Explanation:
 [1,8,17] and [17,8,1] are the valid permutations.
 Example 2:

 Input: [2,2,2]
 Output: 1


 Note:

 1 <= A.length <= 12
 0 <= A[i] <= 1e9
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

class Solution {
private:
    void dfs(int num, int length, unordered_map<int, int>& count, unordered_map<int, unordered_set<int>>& adj, int& result) {
        count[num] -= 1;
        if (length == 0) {
            result += 1;
        }

        // cause we use set to store adjacent element, so every permutation will be count only once
        for (int next : adj[num]) {
            if (count[next] != 0) {
                dfs(next, length - 1, count, adj, result);
            }
        }
        count[num] += 1;
    }
public:
    int numSquarefulPerms(vector<int>& A) {
        unordered_map<int, int> count;
        for (int a : A) {
            count[a] += 1;
        }

        unordered_map<int, unordered_set<int>> adj;
        for (auto& i : count) {
            for (auto& j : count) {
                int n1 = i.first;
                int n2 = j.first;
                int root = sqrt(n1 + n2);
                if (root * root == n1 + n2) {
                    adj[n1].insert(n2);
                }
            }
        }

        int result = 0;
        for (auto& it : count) {
            dfs(it.first, A.size() - 1, count, adj, result);
        }
        return result;
    }
};
