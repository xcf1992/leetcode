/*
1273. Delete Tree Nodes
https://leetcode.com/problems/delete-tree-nodes/

A tree rooted at node 0 is given as follows:
The number of nodes is nodes;
The value of the i-th node is value[i];
The parent of the i-th node is parent[i].

Remove every subtree whose sum of values of nodes is zero.
After doing so, return the number of nodes remaining in the tree.

Example 1:
Input: nodes = 7, parent = [-1,0,0,1,2,2,2], value = [1,-2,4,0,-2,-1,-1]
Output: 2

Constraints:
1 <= nodes <= 10^4
-10^5 <= value[i] <= 10^5
parent.length == nodes
parent[0] == -1 which indicates that 0 is the root.
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
using namespace std;

class Solution {
private:
    pair<int, int> getSubTreeSum(vector<vector<int> > &child, vector<int> &parent, vector<int> &value, int root) {
        int sum = value[root];
        int count = 1;
        for (int next: child[root]) {
            pair<int, int> subSum = getSubTreeSum(child, parent, value, next);
            sum += subSum.first;
            count += subSum.second;
        }

        if (sum == 0) {
            count = 0;
        }
        return {sum, count};
    }

public:
    int deleteTreeNodes(int nodes, vector<int> &parent, vector<int> &value) {
        vector<vector<int> > child(nodes);
        for (int i = 0; i < parent.size(); ++i)
            if (parent[i] != -1) {
                child[parent[i]].push_back(i);
            }
        return getSubTreeSum(child, parent, value, 0).second;
    }
};