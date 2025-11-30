/*
478. Generate Random Point in a Circle
Given the radius and x-y positions of the center of a circle,
write a function randPoint which generates a uniform random point in the circle.

Note:

input and output values are in floating-point.
radius and x-y position of the center of the circle is passed into the class constructor.
a point on the circumference of the circle is considered to be in the circle.
randPoint returns a size 2 array containing x-position and y-position of the random point, in that order.
Example 1:

Input:
["Solution","randPoint","randPoint","randPoint"]
[[1,0,0],[],[],[]]
Output: [null,[-0.72939,-0.65505],[-0.78502,-0.28626],[-0.83119,-0.19803]]
Example 2:

Input:
["Solution","randPoint","randPoint","randPoint"]
[[10,5,-7.5],[],[],[]]
Output: [null,[11.52438,-8.33273],[2.46992,-16.21705],[11.13430,-12.42337]]
Explanation of Input Syntax:

The input is two lists: the subroutines called and their arguments.
Solution's constructor has three arguments,
the radius,
x-position of the center,
and y-position of the center of the circle.
randPoint has no arguments.
Arguments are always wrapped with a list,
even if there aren't any.
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
#include <climits>
#include <set>
#include <numeric>
using namespace std;

// https://stackoverflow.com/questions/5837572/generate-a-random-point-within-a-circle-uniformly/50746409#50746409
class Solution {
private:
    double r;
    double x_c;
    double y_c;
    double pi = 3.14159265358979732384626433832795;

public:
    Solution(double radius, double x_center, double y_center) {
        r = radius;
        x_c = x_center;
        y_c = y_center;
        srand(NULL);
    }

    vector<double> randPoint() {
        double theta = 2 * pi * (double)rand() / RAND_MAX;
        double radius = sqrt((double)rand() / RAND_MAX) * r;
        double x = radius * cos(theta);
        double y = radius * sin(theta);
        return {x + x_c, y + y_c};
    }
};

/*
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj.randPoint();
 */

/*
class Solution {
    double rad, xc, yc;
    public Solution(double radius, double x_center, double y_center) {
        rad = radius;
        xc = x_center;
        yc = y_center;
    }

    public double[] randPoint() {
        double x0 = xc - rad;
        double y0 = yc - rad;

        while(true) {
            double xg = x0 + Math.random() * rad * 2;
            double yg = y0 + Math.random() * rad * 2;
            if (Math.sqrt(Math.pow((xg - xc) , 2) + Math.pow((yg - yc), 2)) <= rad)
                return new double[]{xg, yg};
        }
    }
}
*/