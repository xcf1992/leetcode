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

/*
 Forget about two jugs pouring between each other, which may make you confused.
 
 Let’s make it simple: assuming we have one big enough bucket and two cups with volume x and y, respectively. 
 Now we want to perform a series of operation – pouring water in and out only by those two cups with exactly amount x or y. 
 Somehow, there will be only z water left in this big bucket eventually. Then the equation will be:
 
 z = m * x + n * y
 m means using cup-x m times. If m is positive, it means pouring in. Otherwise, it’s pouring out.
 n is similar.
 
 For example, 4 = (-2) * 3 + 2 * 5, which means you pour in water twice with cup-5 
 and pour out water twice with cup-3. 
 Talk back to the question, it’s like we first fill jug-5, 
 pour water to jug-3 from jug-5, empty jug-3, pour the remaining 2 water into jug-3 from jug-5, 
 fill jug-5 again, pour water into jug-3 from jug-5, empty jug-3, 
 then we have only 4 water left in jug-5. It’s exactly fill jug-5 twice and empty jug-3 twice.
 
 Now the question is, can we find those two m and n exist?
 
 The answer is YES. Here we need a little math – Bezout’s identity, which is:
 
 We can always find a and b to satisfy ax + bx = d where d = gcd(x, y)
 
 So, everything is clear, if z % d == 0, then we have (a*z/d)*x + (b*z/d)*y = z, which means m and n exist.
 
 Below is the code:
 */
class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        return z == 0 || (x + y >= z && z % gcd(x, y) == 0);
    }
private:
    int gcd(int x, int y) {
        if (x < y) {
            return gcd(y, x);
        }
        return y == 0 ? x : gcd(y, x % y);
    }
};

/*
class Solution(object):
    def canMeasureWater(self, x, y, z):
        """
        :type x: int
        :type y: int
        :type z: int
        :rtype: bool
        """
        if x > y:
            temp = x;
            x = y;
            y = temp;
            
        if z > x + y:
            return False;
        
        # set the initial state will empty jars;
        queue = [(0, 0)];
        visited = set((0, 0));
        while len(queue) > 0:
            a, b = queue.pop(0);
            if a + b == z:
                return True;
            
            states = set()
            
            states.add((x, b)) # fill jar x;
            states.add((a, y)) # fill jar y;
            states.add((0, b)) # empty jar x;
            states.add((a, 0)) # empty jar y;
            states.add((min(x, b + a), 0 if b < x - a else b - (x - a))) # pour jar y to x;
            states.add((0 if a + b < y else a - (y - b), min(b + a, y))) # pour jar x to y;

            for state in states:
                if state in visited:
                    continue;
                queue.append(state)
                visited.add(state);
                
        return False;
*/
