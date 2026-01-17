/*
https://leetcode.com/problems/count-number-of-rectangles-containing-each-point/description/
2250. Count Number of Rectangles Containing Each Point

You are given a 2D integer array rectangles where rectangles[i] = [li, hi] indicates that ith rectangle has a length of
li and a height of hi. You are also given a 2D integer array points where points[j] = [xj, yj] is a point with
coordinates (xj, yj).

The ith rectangle has its bottom-left corner point at the coordinates (0, 0) and its top-right corner point at (li, hi).

Return an integer array count of length points.length where count[j] is the number of rectangles that contain the jth
point.

The ith rectangle contains the jth point if 0 <= xj <= li and 0 <= yj <= hi. Note that points that lie on the edges of a
rectangle are also considered to be contained by that rectangle.



Example 1:


Input: rectangles = [[1,2],[2,3],[2,5]], points = [[2,1],[1,4]]
Output: [2,1]
Explanation:
The first rectangle contains no points.
The second rectangle contains only the point (2, 1).
The third rectangle contains the points (2, 1) and (1, 4).
The number of rectangles that contain the point (2, 1) is 2.
The number of rectangles that contain the point (1, 4) is 1.
Therefore, we return [2, 1].
Example 2:


Input: rectangles = [[1,1],[2,2],[3,3]], points = [[1,3],[1,1]]
Output: [1,3]
Explanation:
The first rectangle contains only the point (1, 1).
The second rectangle contains only the point (1, 1).
The third rectangle contains the points (1, 3) and (1, 1).
The number of rectangles that contain the point (1, 3) is 1.
The number of rectangles that contain the point (1, 1) is 3.
Therefore, we return [1, 3].


Constraints:

1 <= rectangles.length, points.length <= 5 * 104
rectangles[i].length == points[j].length == 2
1 <= li, xj <= 109
1 <= hi, yj <= 100
All the rectangles are unique.
All the points are unique.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <stack>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {
        sort(rectangles.begin(), rectangles.end(), [](vector<int> a, vector<int> b) {
            return a[1] < b[1];
        });

        map<int, vector<int>> sorted_rect;
        for (vector<int>& rect : rectangles) {
            int x = rect[0];
            int y = rect[1];
            if (sorted_rect.find(x) == sorted_rect.end()) {
                sorted_rect[x] = vector<int>();
            }
            sorted_rect[x].push_back(y);
        }

        int n = points.size();
        vector<int> rst(n, 0);
        for (int i = 0; i < n; i++) {
            int x = points[i][0];
            int y = points[i][1];
            int cnt = 0;
            for (auto it = sorted_rect.lower_bound(x); it != sorted_rect.end(); ++it) {
                vector<int>& rect_y = it->second;
                cnt += rect_y.end() - lower_bound(rect_y.begin(), rect_y.end(), y);
            }
            rst[i] = cnt;
        }
        return rst;
    }
};

class Solution {
public:

    // helper fxn for binary search
    int binsear(vector<int>& arr, int x){
        int l=0, r=arr.size()-1;

        int anstillnow=arr.size();
        // if we find no m such that arr[m]>=x, means that our x is greater than all values of length, in such case we return idx n (i.e. size of arr)
        // reason being, we substract our idx by size of arr to get number of rectangles greater than that in main fxn, so return arr.size would give us 0 (which we want)

        while(l<=r){
            int m= l + (r-l)/2;


            if(arr[m]>=x){
                anstillnow=m;
                r=m-1;
            }
            else{
                l=m+1;
            }

        }

        return anstillnow;
    }


    vector<int> countRectangles(vector<vector<int>>& rect, vector<vector<int>>& points) {

        unordered_map<int, vector<int>> htl;
        // maps heights to all the lengths of rectangles with that height

        for(int i=0; i<rect.size(); i++){
            htl[rect[i][1]].push_back(rect[i][0]);
        }

        // have to sort the containers to apply binary search
        for(int i=0; i<=100; i++){
            sort(htl[i].begin(), htl[i].end());
        }


        vector<int> ans;

        for(vector<int> p: points){
            int x=p[0], y=p[1];
            int ct=0;
            for(int j= y; j<=100; j++){
                if(htl.find(j)!=htl.end()){
                    ct+= htl[j].size()- binsear(htl[j], x);
                    // binary search return the idx in array from which the values are >= x
                    // the values at this and right of this are the lengths possible
                    // so substract by size of array to get the number
                }
            }

            ans.push_back(ct);

        }

        return ans;
    }
};