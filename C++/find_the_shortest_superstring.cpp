/*
 Given an array A of strings, find any smallest string that contains each string in A as a substring.
 
 We may assume that no string in A is substring of another string in A.
 
 
 Example 1:
 
 Input: ["alex","loves","leetcode"]
 Output: "alexlovesleetcode"
 Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
 Example 2:
 
 Input: ["catg","ctaagt","gcta","ttca","atgcatc"]
 Output: "gctaagttcatgcatc"
 
 
 Note:
 
 1 <= A.length <= 12
 1 <= A[i].length <= 20
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
 graph[i][j] means the length of string to append when A[i] followed by A[j]. eg. A[i] = abcd, A[j] = bcde, then graph[i][j] = 1
 Then the problem becomes to: find the shortest path in this graph which visits every node exactly once. This is a Travelling Salesman Problem.
 Apply TSP DP solution. Remember to record the path.
 Time complexity: O(n^2 * 2^n)
 https://en.wikipedia.org/wiki/Held%E2%80%93Karp_algorithm
 https://leetcode.com/problems/find-the-shortest-superstring/discuss/194932/Travelling-Salesman-Problem
 */
class Solution {
private:
    bool startWith(string s, string prefix) {
        for (int i = 0; i < prefix.size(); i++) {
            if (i >= s.size() || s[i] != prefix[i]) {
                return false;
            }
        }
        return true;
    }
    
    int getDistance(string a, string b) {
        for (int i = 0; i < a.size(); i++) {
            string temp = a.substr(i);
            if (startWith(b, temp)) {
                return b.size() - temp.size();
            }
        }
        return b.length();
    }
public:
    string shortestSuperstring(vector<string>& A) {
        int n = A.size();
        vector<vector<int>> graph(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 0; j++) {
                graph[i][j] = getDistance(A[i], A[j]);
            }
        }
        
        vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
        vector<vector<int>> path(1 << n, vector<int>(n, 0));
        int last = -1;
        int shortest = INT_MAX;
    }
};
