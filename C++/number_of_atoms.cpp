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
private:
    map<string, int> count(string formula, int& start) {
        map<string, int> atoms;
        if (start >= formula.size()) {
            return atoms;
        }
        
        while (start < formula.size()) {
            char letter = formula[start];
            
            if (letter == ')') {
                start += 1;
                return atoms;
            }
            else if (letter == '(') {
                start += 1;
                map<string, int> subAtoms = count(formula, start);
                
                int num = 1;
                int end = start;
                while (end < formula.size() && formula[end] >= '0' && formula[end] <= '9') {
                    end += 1;
                }
                if (end != start) {
                    num = stoi(formula.substr(start, end - start));
                }
                
                for (auto it = subAtoms.begin(); it != subAtoms.end(); it++) {
                    atoms[it -> first] += ((it -> second) * num);
                }
                start = end;
            }
            else if (letter >= 'A' && letter <= 'Z') {
                int end = start + 1;
                while (end < formula.size() && formula[end] >= 'a' && formula[end] <= 'z') {
                    end += 1;
                }
                string atom = formula.substr(start, end - start);
                
                start = end;
                end = start;
                while (end < formula.size() && formula[end] >= '0' && formula[end] <= '9') {
                    end += 1;
                }
                atoms[atom] += end == start ? 1 : stoi(formula.substr(start, end - start));
                
                start = end;
            }
        }
        
        return atoms;
    }
public:
    string countOfAtoms(string formula) {
        string result = "";
        int start = 0;
        map<string, int> atomNum = count(formula, start);
        for (pair<string, int> p : atomNum) {
            result += p.first;
            if (p.second > 1) {
                result += to_string(p.second);
            }
        }
        return result;
    }
};
