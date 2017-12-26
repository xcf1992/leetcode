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
        int negative = 1;
        int move = 1;
        while (i < equation.size()) {
            if (equation[i] == 'x') {
                coefficient += negative * move;
                i++;
            }
            else if (equation[i] == '-') {
                negative = -1;
                i++;
            }
            else if (equation[i] == '+') {
                negative = 1;
                i++;
            }
            else if (equation[i] >= '0' && equation[i] <= '9') {
                int start = i;
                while (equation[i] >= '0' && equation[i] <= '9') {
                    i++;
                }
                int value = stoi(equation.substr(start, i - start));
                if (equation[i] == 'x') {
                    coefficient += negative * value * move;
                    i++;
                }
                else {
                    num -= negative * value * move;
                }
            }
            else if (equation[i] == '=') {
                negative = 1;
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