/*
 391. Perfect Rectangle

 Given N axis-aligned rectangles where N > 0, determine if they all together form an exact cover of a rectangular region.

 Each rectangle is represented as a bottom-left point and a top-right point. For example, a unit square is represented as [1,1,2,2]. (coordinate of bottom-left point is (1, 1) and top-right point is (2, 2)).


 Example 1:

 rectangles = [
 [1,1,3,3],
 [3,1,4,2],
 [3,2,4,4],
 [1,3,2,4],
 [2,3,3,4]
 ]

 Return true. All 5 rectangles together form an exact cover of a rectangular region.




 Example 2:

 rectangles = [
 [1,1,2,3],
 [1,3,2,4],
 [3,1,4,2],
 [3,2,4,4]
 ]

 Return false. Because there is a gap between the two rectangular regions.




 Example 3:

 rectangles = [
 [1,1,3,3],
 [3,1,4,2],
 [1,3,2,4],
 [3,2,4,4]
 ]

 Return false. Because there is a gap in the top center.




 Example 4:

 rectangles = [
 [1,1,3,3],
 [3,1,4,2],
 [1,3,2,4],
 [2,2,4,4]
 ]

 Return false. Because two of the rectangles overlap with each other.
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
 The right answer must satisfy two conditions:

 the large rectangle area should be equal to the sum of small rectangles
 count of all the points should be even, and that of all the four corner points should be one

 Proof to condition 1 is straightforward so I will focus on condition 2.
 First by observation we know it holds true for a perfect rectangle
 (consider how many small rectangles can overlap at a particular point:
  the number has to be even except for the four corner points of the prefect rectangle).

The real question is whether it can also be true for some non-perfect rectangle.
 Let's begin with the question: what will a non-perfect rectangle look like?
 Of course it can look rather complicated but here is a simple way to define it:
 any non-perfect rectangle can be obtained by a sequence of adding or removing rectangular parts from its perfect counterpart
 (the order for adding or removing does not matter here).
 If condition 1 is held true, the non-perfect rectangle must be built by both adding
 and removing small rectangles such that the total area of added rectangles compensates for those of removed.

 Without loss of generality,
 let's focus on the first rectangle (denoted as FR) that is being removed
 (i.e., we have perfect rectangle before removing it).
 FR has four corner points.
 Before removing it, each corner points will appear even times
 (here I assume FR does not contain any corner points of the perfect rectangle.
 See my comment below for more details).
 After it's gone, all the four corner points will appear odd times.
 To make condition 2 valid again, for each of these four points,
 we have to either add or remove a rectangle such that each of them will once again appear even times.
 The key here is that the total number of rectangles added or removed is at least two,
 since the added or removed rectangles cannot overlap with FR,
 therefore each added or removed rectangle can contain at most two of the four corner points of FR.

 So we end up with at least two extra rectangles (either added or removed),
 with a total of eight corner points.
 Four of those points coincide with the four corner points of FR.
 What about the other four points?
 For each of these points, if it belongs to a rectangle that is being removed,
 then before removing, it must appear even times and after removing,
 it will appear odd times.
 If it belongs to a rectangle that is being added,
 no matter it coincides with any point in the perfect rectangle or not,
 its number of appearance will always be odd (appear once if does not coincide with any point,
 odd if it does since the original number of appearance before adding is even).
 In either case (adding or removing rectangle),
 there is no way to keep the number of appearance of all points even,
 therefore condition 2 cannot be true for non-perfect rectangles.
 */
class Solution {
private:
    void updatePoints(unordered_set<string>& points, vector<int>& rect) {
        string p1 = to_string(rect[0]) + "_" + to_string(rect[1]);
        string p2 = to_string(rect[0]) + "_" + to_string(rect[3]);
        string p3 = to_string(rect[2]) + "_" + to_string(rect[3]);
        string p4 = to_string(rect[2]) + "_" + to_string(rect[1]);
        if (points.find(p1) == points.end()) {
            points.insert(p1);
        }
        else {
            points.erase(p1);
        }
        if (points.find(p2) == points.end()) {
            points.insert(p2);
        }
        else {
            points.erase(p2);
        }
        if (points.find(p3) == points.end()) {
            points.insert(p3);
        }
        else {
            points.erase(p3);
        }
        if (points.find(p4) == points.end()) {
            points.insert(p4);
        }
        else {
            points.erase(p4);
        }
    }

    bool isValid(unordered_set<string>& points, int leftX, int leftY, int rightX, int rightY) {
        if (points.find(to_string(leftX) + "_" + to_string(leftY)) == points.end()) {
            return false;
        }
        if (points.find(to_string(leftX) + "_" + to_string(rightY)) == points.end()) {
            return false;
        }
        if (points.find(to_string(rightX) + "_" + to_string(leftY)) == points.end()) {
            return false;
        }
        if (points.find(to_string(rightX) + "_" + to_string(rightY)) == points.end()) {
            return false;
        }
        if (points.size() != 4) {
            return false;
        }
        return true;
    }
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        int n = rectangles.size();
        int leftX = INT_MAX, rightX = INT_MIN;
        int leftY = INT_MAX, rightY = INT_MIN;
        int area = 0;
        unordered_set<string> points;
        for (vector<int>& rect : rectangles) {
            leftX = min(leftX, rect[0]);
            leftY = min(leftY, rect[1]);
            rightX = max(rightX, rect[2]);
            rightY = max(rightY, rect[3]);
            area += (rect[2] - rect[0]) * (rect[3] - rect[1]);
            updatePoints(points, rect);
        }
        return isValid(points, leftX, leftY, rightX, rightY) and area == (rightX - leftX) * (rightY - leftY);
    }
};

// wrong [[0,0,1,1],[0,1,3,2],[1,0,2,2]]
class Solution1 {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        int leftX = rectangles[0][0], leftY = rectangles[0][1];
        int rightX = rectangles[0][2], rightY = rectangles[0][3];
        int sum = (rightX - leftX) * (rightY - leftY);
        for (int i = 1; i < rectangles.size(); i++) {
            if (rectangles[i][0] <= leftX and rectangles[i][1] <= leftY) {
                leftX = rectangles[i][0];
                leftY = rectangles[i][1];
            }
            if (rectangles[i][2] >= rightX and rectangles[i][3] >= rightY) {
                rightX = rectangles[i][2];
                rightY = rectangles[i][3];
            }
            sum += (rectangles[i][2] - rectangles[i][0]) * (rectangles[i][3] - rectangles[i][1]);
        }
        return sum == (rightX - leftX) * (rightY - leftY);
    }
};
