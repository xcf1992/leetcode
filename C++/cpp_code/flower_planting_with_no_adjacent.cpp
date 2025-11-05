/*
 1042. Flower Planting With No Adjacent

 You have N gardens, labelled 1 to N.  In each garden, you want to plant one of 4 types of flowers.

 paths[i] = [x, y] describes the existence of a bidirectional path from garden x to garden y.

 Also, there is no garden that has more than 3 paths coming into or leaving it.

 Your task is to choose a flower type for each garden such that, for any two gardens connected by a path, they have different types of flowers.

 Return any such a choice as an array answer, where answer[i] is the type of flower planted in the (i+1)-th garden.  The flower types are denoted 1, 2, 3, or 4.  It is guaranteed an answer exists.



 Example 1:

 Input: N = 3, paths = [[1,2],[2,3],[3,1]]
 Output: [1,2,3]
 Example 2:

 Input: N = 4, paths = [[1,2],[3,4]]
 Output: [1,2,1,2]
 Example 3:

 Input: N = 4, paths = [[1,2],[2,3],[3,4],[4,1],[1,3],[2,4]]
 Output: [1,2,3,4]


 Note:

 1 <= N <= 10000
 0 <= paths.size <= 20000
 No garden has 4 or more paths coming into or leaving it.
 It is guaranteed an answer exists.
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
public:
    vector<int> gardenNoAdj(int N, vector<vector<int> > &paths) {
        vector<vector<int> > connected(N);
        for (vector<int> &path: paths) {
            connected[path[0] - 1].push_back(path[1] - 1);
            connected[path[1] - 1].push_back(path[0] - 1);
        }

        vector<int> result(N, 0);
        for (int i = 0; i < N; ++i) {
            unordered_set<int> used;
            for (int j: connected[i]) {
                if (result[j] != 0) {
                    used.insert(result[j]);
                }
            }
            for (int color = 1; color <= 4; ++color) {
                if (used.find(color) == used.end()) {
                    result[i] = color;
                }
            }
        }
        return result;
    }
};