/*
587. Erect the Fence
There are some trees, where each tree is represented by (x,y) coordinate in a two-dimensional garden.
Your job is to fence the entire garden using the minimum length of rope as it is expensive.
The garden is well fenced only if all the trees are enclosed.
Your task is to help find the coordinates of trees which are exactly located on the fence perimeter.


Example 1:

Input: [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
Explanation:

Example 2:

Input: [[1,2],[2,2],[4,2]]
Output: [[1,2],[2,2],[4,2]]
Explanation:

Even you only have trees in a line, you need to use rope to enclose them.


Note:

All trees should be enclosed together. You cannot cut the rope to enclose trees that will separate them in more than one group.
All input integers will range from 0 to 100.
The garden has at least one tree.
All coordinates are distinct.
Input points have NO order. No order required for output.
input types have been changed on April 15, 2019. pointslease reset to default code definition to get new method signature.
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

// https://www.algorithmist.com/index.php/Monotone_Chain_Convex_Hull.cpp
// https://www.geeksforgeeks.org/convex-hull-monotone-chain-algorithm/
// https://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/
// https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
// https://www.geeksforgeeks.org/orientation-3-ordered-points/

typedef int coord_t; // coordinate type
typedef long long coord2_t; // must be big enough to hold 2*max(|coordinate|)^2

class Solution {
private:
    /*
    * 2D cross product of OA and OB vectors,
    * i.e. z-component of their 3D cross product.
    * Returns a positive value, if OAB makes a counter-clockwise turn,
    * negative for clockwise turn,
    * and zero if the points are collinear.
   */
    coord2_t cross(const vector<int> &O, const vector<int> &A, const vector<int> &B) {
        return (A[0] - O[0]) * (coord2_t) (B[1] - O[1]) - (A[1] - O[1]) * (coord2_t) (B[0] - O[0]);
    }

    static bool cmp(vector<int> &p1, vector<int> &p2) {
        // from left to right, from bot to top
        return p1[0] < p2[0]
        or(p1[0] == p2[0] and p1[1] < p2[1]);
    }

    static bool equ(vector<int> &p1, vector<int> &p2) {
        return p1[0] == p2[0]
        and p1[1]
        ==
        p2[1];
    }

public:
    // Returns a list of points on the convex hull in counter-clockwise order.
    // Note: the last point in the returned list is the same as the first one.
    vector<vector<int> > outerTrees(vector<vector<int> > &points) {
        int n = points.size();
        int k = 0;
        vector<vector<int> > result(2 * n);

        // Sort points lexicographically
        sort(points.begin(), points.end(), cmp);

        // Build lower hull
        for (int i = 0; i < n; i++) {
            // If the point at K-1 position is not a part
            // of hull as vector from ans[k-2] to ans[k-1]
            // and ans[k-2] to A[i] has a clockwise turn
            while (k >= 2 and cross(result[k - 2], result[k - 1], points[i])
            <
            0
            )
            {
                k--;
            }
            result[k] = points[i];
            k += 1;
        }

        // Build upper hull
        // start from n - 2 cause point(n - 1) which is the rightmost point is already in the return result
        for (int i = n - 2, t = k + 1; i >= 0; i--) {
            // If the point at K-1 position is not a part
            // of hull as vector from ans[k-2] to ans[k-1]
            // and ans[k-2] to A[i] has a clockwise turn
            while (k >= t and cross(result[k - 2], result[k - 1], points[i])
            <
            0
            )
            {
                k--;
            }
            result[k] = points[i];
            k += 1;
        }

        // Remove duplicates
        result.resize(k);
        sort(result.begin(), result.end(), cmp);
        result.erase(unique(result.begin(), result.end(), equ), result.end());
        return result;
    }
};