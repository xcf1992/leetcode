/*
 You are given two jugs with capacities x and y litres. There is an infinite amount of water supply available. You need to determine whether it is possible to measure exactly z litres using these two jugs.
 
 If z liters of water is measurable, you must have z liters of water contained within one or both buckets by the end.
 
 Operations allowed:
 
 Fill any of the jugs completely with water.
 Empty any of the jugs.
 Pour water from one jug into another till the other jug is completely full or the first jug itself is empty.
 Example 1: (From the famous "Die Hard" example)
 
 Input: x = 3, y = 5, z = 4
 Output: True
 Example 2:
 
 Input: x = 2, y = 6, z = 5
 Output: False
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
#include <set>
using namespace std;

class Solution1 {
private:
    int X;
    int Y;
    int Z;
    bool find;
    
    void dfs(int curX, int curY, vector<vector<bool>>& visited) {
        if (visited[curX][curY] || find) {
            return;
        }
        if (curX == Z || curY == Z) {
            find = true;
            return;
        }
        visited[curX][curY] = true;
        if (curX != 0) {
            dfs(0, curY, visited);
            if (find) {
                return;
            }
        }
        if (curY != 0) {
            dfs(curX, 0, visited);
            if (find) {
                return;
            }
        }
        if (curX != X) {
            dfs(X, curY, visited);
            if (find) {
                return;
            }
        }
        if (curY != Y) {
            dfs(curX, Y, visited);
            if (find) {
                return;
            }
        }
        if (curX != X) {
            int gap = X - curX;
            if (gap > curY) {
                dfs(curX + curY, 0, visited);
                if (find) {
                    return;
                }
            }
            else {
                dfs(X, curY - gap, visited);
                if (find) {
                    return;
                }
            }
        }
        if (curY != Y) {
            int gap = Y - curY;
            if (gap > curX) {
                dfs(0, curX + curY, visited);
                if (find) {
                    return;
                }
            }
            else {
                dfs(curX - gap, Y, visited);
                if (find) {
                    return;
                }
            }
        }
    }
public:
    bool canMeasureWater(int x, int y, int z) {
        if (z < 0 || z > x + y) {
            return false;
        }
        X = x;
        Y = y;
        Z = z;
        find = false;
        vector<vector<bool>> visited(x + 1, vector<bool>(y + 1, false));
        dfs(0, 0, visited);
        return find;
    }
};

/*
 Forget about two jugs pouring between each other, which may make you confused.
 
 Let’s make it simple: assuming we have one big enough bucket and two cups with volume x and y, respectively. Now we want to perform a series of operation – pouring water in and out only by those two cups with exactly amount x or y. Somehow, there will be only z water left in this big bucket eventually. Then the equation will be:
 
 z = m * x + n * y
 m means using cup-x m times. If m is positive, it means pouring in. Otherwise, it’s pouring out.
 n is similar.
 
 For example, 4 = (-2) * 3 + 2 * 5, which means you pour in water twice with cup-5 and pour out water twice with cup-3. Talk back to the question, it’s like we first fill jug-5, pour water to jug-3 from jug-5, empty jug-3, pour the remaining 2 water into jug-3 from jug-5, fill jug-5 again, pour water into jug-3 from jug-5, empty jug-3, then we have only 4 water left in jug-5. It’s exactly fill jug-5 twice and empty jug-3 twice.
 
 Now the question is, can we find those two m and n exist?
 
 The answer is YES. Here we need a little math – Bezout’s identity, which is:
 
 We can always find a and b to satisfy ax + bx = d where d = gcd(x, y)
 
 So, everything is clear, if z % d == 0, then we have (a*z/d)*x + (b*z/d)*y = z, which means m and n exist.
 
 Below is the code:
 */
class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        return z == 0 || (z - x <= y && z % gcd(x, y) == 0);
    }
private:
    int gcd(int x, int y) {
        return y == 0 ? x : gcd(y, x % y);
    }
};
