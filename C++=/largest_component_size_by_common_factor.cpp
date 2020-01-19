/*
952. Largest Component Size by Common Factor

Given a non-empty array of unique positive integers A, consider the following graph:
There are A.length nodes, labelled A[0] to A[A.length - 1];
There is an edge between A[i] and A[j] if and only if A[i] and A[j] share a common factor greater than 1.
Return the size of the largest connected component in the graph.

Example 1:
Input: [4,6,15,35]
Output: 4

Example 2:
Input: [20,50,9,63]
Output: 2

Example 3:
Input: [2,3,6,7,4,12,21,39]
Output: 8

Note:
1 <= A.length <= 20000
1 <= A[i] <= 100000
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
    void getFactors(int index, int number, unordered_map<int, vector<int>>& factorToIndex) {
        for (int i = 2; i * i <= number; ++i) if (number % i == 0) {
            factorToIndex[i].push_back(index);
            while (number % i == 0) {
                number /= i;
            }
        }

        if (number > 1) {
            factorToIndex[number].push_back(index);
        }
    }

    int find(int index, vector<int>& parent) {
        return parent[index] == -1 ? index : find(parent[index], parent);
    }

    void unin(int index1, int index2, vector<int>& parent, vector<int>& count) {
        int p1 = find(index1, parent);
        int p2 = find(index2, parent);
        if (p1 != p2) {
            parent[p2] = p1;
            count[p1] += count[p2];
            count[p2] = 0;
        }
    }
public:
    int largestComponentSize(vector<int>& A) {
        int n = A.size();
        unordered_map<int, vector<int>> factorToIndex;
        for (int i = 0; i < n; i++) {
            getFactors(i, A[i], factorToIndex);
        }

        vector<int> parent(n, -1);
        vector<int> count(n, 1);
        for (auto& it : factorToIndex) {
            vector<int> connectedIndex = it.second;
            int p = connectedIndex[0];
            for (int i = 1; i < connectedIndex.size(); i++) {
                unin(p, connectedIndex[i], parent, count);
            }
        }

        int result = 1;
        for (int c : count) {
            result = max(result, c);
        }
        return result;
    }
};
