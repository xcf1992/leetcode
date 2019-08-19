/*
640. Solve the Equation
Solve a given equation and return the value of x in the form of string "x=#value".
The equation contains only '+', '-' operation, the variable x and its coefficient.

If there is no solution for the equation, return "No solution".

If there are infinite solutions for the equation, return "Infinite solutions".

If there is exactly one solution for the equation, we ensure that the value of x is an integer.

Example 1:
Input: "x+5-3+x=6+x-2"
Output: "x=2"

Example 2:
Input: "x=x"
Output: "Infinite solutions"

Example 3:
Input: "2x=x"
Output: "x=0"

Example 4:
Input: "2x+3x-6x=x+2"
Output: "x=-1"

Example 5:
Input: "x=x+2"
Output: "No solution"
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
using namespace std;

class Solution {
public:
    string solveEquation(string equation) {
        int coefficient = 0;
        int num = 0;
        int i = 0;
        int positive = 1;
        int move = 1;
        while (i < equation.size()) {
            if (equation[i] == 'x') {
                coefficient += positive * move;
                i++;
            }
            else if (equation[i] == '-') {
                positive = -1;
                i++;
            }
            else if (equation[i] == '+') {
                positive = 1;
                i++;
            }
            else if (isdigit(equation[i])) {
                int start = i;
                while (isdigit(equation[i])) {
                    i++;
                }
                int value = stoi(equation.substr(start, i - start));

                if (equation[i] == 'x') {
                    coefficient += positive * value * move;
                    i++;
                }
                else {
                    num -= positive * value * move;
                }
            }
            else if (equation[i] == '=') {
                positive = 1;
                move = -1;
                i++;
            }
        }

        if (coefficient == 0) {
            return num == 0 ? "Infinite solutions" : "No solution";
        }
        return "x=" + to_string(num / coefficient);
    }
};
